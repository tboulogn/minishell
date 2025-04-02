/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:31:13 by ryada             #+#    #+#             */
/*   Updated: 2025/04/02 09:29:51 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	init_pipe_struct(t_pipe *pro, int cmd_count)
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

void	close_pipe(int *pipefd)
{
	if (pipefd[0] != -1)
		close(pipefd[0]);
	if (pipefd[1] != -1)
		close(pipefd[1]);
}

void	update_pipe(int *prev, int *next)
{
	prev[0] = next[0];
	prev[1] = next[1];
}

void	single_child(t_args *args, t_cmd *cmd, t_env *env_list)
{
	int fd_in;
	int fd_out;

	if (cmd->infile)
	{
		fd_in = open(cmd->infile, O_RDONLY);
		if (fd_in < 0)
			perror(cmd->infile);
		redirect_and_close(fd_in, STDIN_FILENO);
	}
	if (cmd->outfile)
	{
		fd_out = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out < 0)
			perror(cmd->outfile);
		redirect_and_close(fd_out, STDOUT_FILENO);
	}
	if (cmd->append_outfile)
	{
		fd_out = open(cmd->append_outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd_out < 0)
			perror(cmd->append_outfile);
		redirect_and_close(fd_out, STDOUT_FILENO);
	}
	ft_exec(args, &env_list);
}

void	first_child(t_args *args, t_cmd *cmd, t_env *env_list, t_pipe pro)
{
	int	fd;

	close(pro.next[0]);
	if (cmd->infile)
	{
		fd = open(cmd->infile, O_RDONLY);
		if (fd < 0)
			perror(cmd->infile);
		redirect_and_close(fd, STDIN_FILENO);
	}
	redirect_and_close(pro.next[1], STDOUT_FILENO);
	ft_exec(args, &env_list);
}

void	middle_child(t_args *args, t_cmd *cmd, t_env *env_list, t_pipe pro)
{
	int fd_in;
	int fd_out;

	if (cmd->infile)
	{
		fd_in = open(cmd->infile, O_RDONLY);
		if (fd_in < 0)
			perror(cmd->infile);
		redirect_and_close(fd_in, STDIN_FILENO);
	}
	if (cmd->outfile)
	{
		fd_out = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out < 0)
			perror(cmd->outfile);
		redirect_and_close(fd_out, STDOUT_FILENO);
	}
	if (cmd->append_outfile)
	{
		fd_out = open(cmd->append_outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd_out < 0)
			perror(cmd->append_outfile);
		redirect_and_close(fd_in, STDOUT_FILENO);
	}
	close(pro.prev[1]);
	dup2(pro.prev[0], STDIN_FILENO);
	close(pro.prev[0]);
	dup2(pro.next[1], STDOUT_FILENO);
	close(pro.next[1]);
	close(pro.next[0]);
	ft_exec(args, &env_list);
}

void	last_child(t_args *args, t_cmd *cmd, t_env *env_list, t_pipe pro)
{
	int fd_in;
	int fd_out;

	close(pro.prev[1]);
	if (cmd->infile)
	{
		fd_in = open(cmd->infile, O_RDONLY);
		if (fd_in < 0)
			perror(cmd->infile);
		redirect_and_close(fd_in, STDIN_FILENO);
	}
	else
		dup2(pro.prev[0], STDIN_FILENO);
	close(pro.prev[0]);
	if (cmd->outfile)
	{
		fd_out = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out < 0)
			perror(cmd->outfile);
		redirect_and_close(fd_out, STDOUT_FILENO);
	}
	if (cmd->append_outfile)
	{
		fd_out = open(cmd->append_outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd_out < 0)
			perror(cmd->append_outfile);
		redirect_and_close(fd_out, STDOUT_FILENO);
	}
	ft_exec(args, &env_list);
}

void	child_process(t_args *args, t_cmd *cmd, t_env *env_list, t_pipe pro, int i)
{
	if (cmd->here_doc_fd != -1)//if there are any here_doc
	{
		dup2(cmd->here_doc_fd, STDIN_FILENO);
		close(cmd->here_doc_fd);
	}
	if (i == 0)
	{ 
		if (args->cmd_count == 1)
			single_child(args, cmd, env_list);
		else
			first_child(args, cmd, env_list, pro);
	}
	else if (i == args->cmd_count - 1)
		last_child(args, cmd, env_list, pro);
	else
		middle_child(args, cmd, env_list, pro);
	exit(EXIT_SUCCESS);
}

void	wait_children(t_args *args, t_pipe *pro)
{
	int	i;
	int	status;
	int	last_exit;

	i = 0;
	last_exit = 0;
	while (i < args->cmd_count)
	{
		waitpid(pro->pid[i], &status, 0);
		if (WIFEXITED(status))
			last_exit = status;
		i++;
	}
	args->e_status = last_exit;
}

void	single_builtin(t_args *args, t_env **env_list)
{
	int fd_in;
	int fd_out;

	ft_exec(args, env_list);
	// if (args->infile)
	// {
	// 	fd_in = open(args->infile, O_RDONLY);
	// 	if (fd_in < 0)
	// 		perror(args->infile);
	// }
	// if (args->outfile)
	// {
	// 	fd_out = open(args->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// 	if (fd_out < 0)
	// 		perror(args->outfile);
	// }
}

void	set_here_doc_in(t_args *args, t_cmd *current)
{
	int j;
	int hd_fd;

	j = 0;
	while (args->limiter[j])
	{
		hd_fd = ft_here_doc(args->limiter[j]);
		current->here_doc_fd = hd_fd;
		j++;
	}
}

void	pipex(t_args *args, t_env **env_list)
{
    t_pipe pro;
    t_cmd *current;
    t_args temp;
    int i;
	int j;
	int status;
	int hd_fd;

	//if it is only one builtin, we do it manualy, we dont pass it to pipes.
    if (args->cmd_count == 1 && !ft_check_buildin(args))
    {
		single_builtin(args, env_list);
		printf("the last exit status: %d\n", WEXITSTATUS(args->e_status));
        return ;
    }
	//setting the input for here_doc
	j = 0;
	current = args->cmd;
	if (args->limiter)
		set_here_doc_in(args, current);
	//pipes
    i = 0;
    init_pipe_struct(&pro, args->cmd_count);
    while (current)
    {
        ft_memset(&temp, 0, sizeof(t_args));
        temp.cmd = current;
        temp.cmd_count = args->cmd_count;
        if (current->next && pipe(pro.next) == -1)
        {
            perror("pipe");//need to free
            exit(EXIT_FAILURE);
        }
		pro.pid[i] = fork();
        if (pro.pid[i] == -1)
        {
            perror("fork");//need to free
            exit(EXIT_FAILURE);
        }
        if (pro.pid[i] == 0)
            child_process(&temp, current, *env_list, pro, i);
        close_pipe(pro.prev);
        update_pipe(pro.prev, pro.next);
        i++;
        current = current->next;
    }
    close_pipe(pro.prev);
	wait_children(args, &pro);
	printf("the last exit status: %d\n", WEXITSTATUS(args->e_status));
    free(pro.pid);
}
