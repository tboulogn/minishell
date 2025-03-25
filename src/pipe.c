/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:31:13 by ryada             #+#    #+#             */
/*   Updated: 2025/03/25 16:09:41 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void init_pipe_struct(t_pipe *pro, int cmd_count)
{
	pro->pid = malloc(sizeof(pid_t) * cmd_count);
	if (!pro->pid)
	{
		ft_putstr_fd("malloc failed\n", 2);
		exit(EXIT_FAILURE);
	}
	pro->prev[0] = -1;
	pro->prev[1] = -1;
	pro->next[0] = -1;
	pro->next[1] = -1;
}

void close_pipe(int *pipefd)
{
	if (pipefd[0] != -1)
		close(pipefd[0]);
	if (pipefd[1] != -1)
		close(pipefd[1]);
}

void update_pipe(int *prev, int *next)
{
	prev[0] = next[0];
	prev[1] = next[1];
}

void single_child(t_args *args, t_env *env_list)
{
	int fd_open;
	int fd_close;

	if (args->infile)
	{
		fd_open = open(args->infile, O_RDONLY);
		if (fd_open < 0)
			perror(args->infile);
		dup2(fd_open, STDIN_FILENO);
		close(fd_open);
	}
	if (args->outfile)
	{
		fd_close = open(args->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_close < 0)
			perror(args->outfile);
		dup2(fd_close, STDOUT_FILENO);
		close(fd_close);
	}
	ft_exec(args, &env_list);
}

void	first_child(t_args *args, t_env *env_list, t_pipe pro)
{
	int	fd;

	close(pro.next[0]);
	if (args->infile)
	{
		fd = open(args->infile, O_RDONLY);
		if (fd < 0)
			perror(args->infile);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	dup2(pro.next[1], STDOUT_FILENO);
	close(pro.next[1]);
	ft_exec(args, &env_list);
}

void	middle_child(t_args *args, t_env *env_list, t_pipe pro)
{
	close(pro.prev[1]);
	dup2(pro.prev[0], STDIN_FILENO);
	close(pro.prev[0]);
	dup2(pro.next[1], STDOUT_FILENO);
	close(pro.next[1]);
	close(pro.next[0]);
	ft_exec(args, &env_list);
}

void	last_child(t_args *args, t_env *env_list, t_pipe pro)
{
	int	fd;

	close(pro.prev[1]);
	dup2(pro.prev[0], STDIN_FILENO);
	close(pro.prev[0]);
	if (args->outfile)
	{
		fd = open(args->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			perror(args->outfile);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	ft_exec(args, &env_list);
}

void	child_process(t_args *args, t_env *env_list, t_pipe pro, int i)
{
	if (i == 0)
	{ 
		if (args->cmd_count == 1)
			single_child(args, env_list);
		else
			first_child(args, env_list, pro);
	}
	else if (i == args->cmd_count - 1)
		last_child(args, env_list, pro);
	else
		middle_child(args, env_list, pro);
	exit(EXIT_SUCCESS);
}


void	pipex(t_args *args, t_env **env_list)
{
    t_pipe pro;
    t_cmd *current;
    t_args temp;
    int i;
	int fd_in;
	int fd_out;

    if (args->cmd_count == 1 && !ft_check_buildin(args))
    {
        printf("caca");
		ft_exec(args, env_list);
		if (args->infile)
		{
			fd_in = open(args->infile, O_RDONLY);
			if (fd_in < 0)
				perror(args->infile);
		}
		if (args->outfile)
		{
			fd_out = open(args->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd_out < 0)
				perror(args->outfile);
		}
        return ;
    }
    i = 0;
    init_pipe_struct(&pro, args->cmd_count);
    current = args->cmd;
    while (current)
    {
        ft_memset(&temp, 0, sizeof(t_args));
        temp.cmd = current;
        temp.cmd_count = args->cmd_count;
        temp.infile = args->infile;
        temp.outfile = args->outfile;
        if (current->next && pipe(pro.next) == -1)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
        // if (!(args->cmd_count == 1 && ft_check_buildin(args)))
            pro.pid[i] = fork();
        if (pro.pid[i] == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (pro.pid[i] == 0)
            child_process(&temp, *env_list, pro, i);
        close_pipe(pro.prev);
        update_pipe(pro.prev, pro.next);
        i++;
        current = current->next;
    }
    close_pipe(pro.prev);
    while (wait(NULL) > 0);
    free(pro.pid);
}
