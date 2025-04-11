/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:31:13 by ryada             #+#    #+#             */
/*   Updated: 2025/04/11 11:32:42 by ryada            ###   ########.fr       */
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

void close_parent_pipes(t_pipe *pro)
{
	if (pro->prev[0] != -1)
		close(pro->prev[0]);
	if (pro->prev[1] != -1)
		close(pro->prev[1]);
}

void close_child_pipes(t_pipe *pro)
{
	if (pro->prev[0] != -1)
		close(pro->prev[0]);
	if (pro->prev[1] != -1)
		close(pro->prev[1]);
	if (pro->next[0] != -1)
		close(pro->next[0]);
	if (pro->next[1] != -1)
		close(pro->next[1]);
}

void	update_pipe(int *prev, int *next)
{
	prev[0] = next[0];
	prev[1] = next[1];
}

void	read_files(t_cmd *cmd, int fd, int type)
{
	if (type == 1)//infile
	{
		fd= open(cmd->infile, O_RDONLY);
		if (fd < 0)
			perror(cmd->infile);
		redirect_and_close(fd, STDIN_FILENO);
	}
	else if (type == 2)//outfile (non-append)
	{
		fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			perror(cmd->outfile);
		redirect_and_close(fd, STDOUT_FILENO);
	}
	else if (type == 3)//outfile (append)
	{
		fd = open(cmd->append_outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
			perror(cmd->append_outfile);
		redirect_and_close(fd, STDOUT_FILENO);
	}
}

void	single_child(t_args *args, t_cmd *cmd, t_env *env_list, t_pipe pro)
{
	int fd_in;
	int fd_out;

	if (cmd->infile)
		read_files(cmd, fd_in, 1);
	if (cmd->outfile)
		read_files(cmd, fd_out, 2);
	if (cmd->append_outfile)
		read_files(cmd, fd_out, 3);
	ft_exec(args, &env_list, &pro);
}

void	first_child(t_args *args, t_cmd *cmd, t_env *env_list, t_pipe pro)
{
	int	fd;

	close(pro.next[0]);
	if (cmd->infile)
		read_files(cmd, fd, 1);
	else
		dup2(pro.prev[0], STDIN_FILENO);
	redirect_and_close(pro.next[1], STDOUT_FILENO);
	ft_exec(args, &env_list, &pro);
}

void	middle_child(t_args *args, t_cmd *cmd, t_env *env_list, t_pipe pro)
{
	int fd_in;
	int fd_out;

	if (cmd->infile)
		read_files(cmd, fd_in, 1);
	if (cmd->outfile)
		read_files(cmd, fd_out, 2);
	if (cmd->append_outfile)
		read_files(cmd, fd_out, 3);
	dup2(pro.prev[0], STDIN_FILENO);
	dup2(pro.next[1], STDOUT_FILENO);
	close_child_pipes(&pro);
	ft_exec(args, &env_list, &pro);
}

void	last_child(t_args *args, t_cmd *cmd, t_env *env_list, t_pipe pro)
{
	int fd_in;
	int fd_out;

	close(pro.prev[1]);
	if (cmd->infile)
		read_files(cmd, fd_in, 1);
	else
		dup2(pro.prev[0], STDIN_FILENO);
	close(pro.prev[0]);
	if (cmd->outfile)
		read_files(cmd, fd_out, 2);
	if (cmd->append_outfile)
		read_files(cmd, fd_out, 3);
	ft_exec(args, &env_list, &pro);
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
			single_child(args, cmd, env_list, pro);
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
		if (i++ == args->cmd_count - 1)
		{
			if (WIFEXITED(status))
				last_exit = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGQUIT)
					write(1, "Quit (core dumped)\n", 20);
				else if (WTERMSIG(status) == SIGINT)
					write(1, "\n", 1);
				last_exit = 128 + WTERMSIG(status);
			}
		}
	}
	g_signal = last_exit;
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

int	no_files(t_cmd *cmd)
{
	if (!cmd->infile && !cmd->outfile && !cmd->append_outfile)
		return (1);
	return (0);
}

void	handle_pipe_and_fork(t_pipe	*pro, t_cmd *current, int i)
{
	if (current->next && pipe(pro->next) == -1)
	{
		perror("pipe");
		free(pro->pid);
		exit(EXIT_FAILURE);
	}
	pro->pid[i] = fork();
	if (pro->pid[i] == -1)
	{
		perror("fork");
		free(pro->pid);
		exit(EXIT_FAILURE);
	}
}

void	init_temp_args(t_args *temp, t_cmd *current, int cmd_count)
{
	ft_memset(temp, 0, sizeof(t_args));
	temp->cmd = current;
	temp->cmd_count = cmd_count;
}

void	close_and_update(t_pipe *pro)
{
	close_parent_pipes(pro);
	update_pipe(pro->prev, pro->next);
}

void	pipex(t_args *args, t_env **env_list)
{
	t_pipe	pro;
	t_cmd	*current;
	t_args	*temp;
	int 	i;
	int 	j;
	int 	fd;

	current = args->cmd;
	if (args->limiter && args->cmd_count == 0)
	{
		j = 0;
		while (args->limiter[j])
		{
			fd = ft_here_doc(args->limiter[j]);
			close(fd);
			j++;
		}
		return ;
	}
	if (args->limiter)
		set_here_doc_in(args, current);
	else if (args->cmd_count == 1 && !ft_check_buildin(args) && no_files(current))
		return (ft_exec(args, env_list, &pro));
	init_pipe_struct(&pro, args->cmd_count);
	i = 0;
	while(current)
	{
		temp = malloc(sizeof(t_args));
		init_temp_args(temp, current, args->cmd_count);
		handle_pipe_and_fork(&pro, current, i);
		if (pro.pid[i] == 0)
		{
			ignore_parent_signals();
			child_process(temp, current, *env_list, pro, i);
		}
		free(temp);
		close_and_update(&pro);
		current = current->next;
		i++;
	}
	close_parent_pipes(&pro);
	wait_children(args, &pro);
	free(pro.pid);
}

