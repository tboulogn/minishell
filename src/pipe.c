/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:31:13 by ryada             #+#    #+#             */
/*   Updated: 2025/03/24 17:11:30 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	ft_close_pipe(int *pipe)
// {
// 	if (pipe[0] != -1)
// 		close(pipe[0]);
// 	if (pipe[1] != -1)
// 		close(pipe[1]);
// }

// void	ft_update_pipe(int *prev, int *next)
// {
// 	prev[0] = next[0];
// 	prev[1] = next[1];
// }

// void	ft_first_child(t_args *args, t_env *env_list, t_pipe pro)
// {
// 	int	fd;

// 	close(pro.next[0]);
// 	// if (!edata.here_doc)
// 	// {
// 	// 	fd = ft_open_file(argv[1], 2, edata.pid);
// 	// 	dup2(fd, STDIN_FILENO);
// 	// 	close(fd);
// 	// }
// 	dup2(pro.next[1], STDOUT_FILENO);
// 	close(pro.next[1]);
// 	// if (edata.here_doc)
// 	// 	ft_exec(argv[3], envp, edata.pid);
// 	// else
// 	ft_exec(args, env_list);
// }

// void	ft_middle_child(t_args *args, t_env *env_list, t_pipe pro)
// {
// 	close(pro.prev[1]);
// 	dup2(pro.prev[0], STDIN_FILENO);
// 	close(pro.prev[0]);
// 	dup2(pro.next[1], STDOUT_FILENO);
// 	close(pro.next[1]);
// 	close(pro.next[0]);
// 	ft_exec(args, env_list);
// }

// void	ft_last_child(t_args *args, t_env *env_list, t_pipe pro)
// {
// 	// int	fd;
// 	// int	argc;

// 	// argc = ft_arg_count(argv);
// 	close(pro.prev[1]);
// 	// if (!edata.here_doc)
// 	// 	fd = ft_open_file(argv[argc - 1], 1, edata.pid);
// 	// else
// 	// 	fd = ft_open_file(argv[argc - 1], 0, edata.pid);
// 	dup2(STDOUT_FILENO, pro.next[1]);
// 	close(pro.next[1]);
// 	dup2(pro.prev[0], STDIN_FILENO);
// 	close(pro.prev[0]);
// 	ft_exec(args, env_list);
// }

// void	ft_child_process(t_args *args, t_env *env_list, t_pipe pro, int i)
// {
// 	if (i == 0)
// 		ft_first_child(args, env_list, pro);
// 	else if (i == args->cmd_count - 1)
// 		ft_last_child(args, env_list, pro);
// 	else
// 		ft_middle_child(args, env_list, pro);
// 	// exit(EXIT_SUCCESS);
// }

// void	ft_create_process(t_args *args, t_env *env_list, t_pipe pro)
// {
// 	int     i;
//     int     cmd_count;
// 	pid_t	*pid;

// 	i = 0;
//     cmd_count = args->cmd_count;
//     pid = malloc(sizeof(pid) * cmd_count);
//     if (!pid)
//     {
// 		ft_putstr_fd("Malloc faild!\n", 2);
// 		exit (1);
// 		// ft_general_error_handler(edata, 1);
//     }
// 	pro.prev[1] = -1;
// 	while (i < args->pipe)
// 	{
// 		if (pipe(pro.next) == -1)
//         {
//             ft_putstr_fd("pipe creation faild!\n", 2);
//             exit (1);
// 			// ft_general_error_handler(edata, 1);
//         }
// 		pid[i] = fork();
// 		if (pid[i] == -1)
//         {
//             ft_putstr_fd("fork faild!\n", 2);
//             exit (1);
// 			// ft_general_error_handler(edata, 2);
//         }
// 		if (pid[i] == 0)
// 			ft_child_process(args, env_list, pro, i);
// 		ft_close_pipe(pro.prev);
// 		ft_update_pipe(pro.prev, pro.next);
// 		i++;
// 	}
// 	ft_close_pipe(pro.prev);
// }

// // void	ft_wait_children(t_edata *edata)
// // {
// // 	int	i;
// // 	int	status;
// // 	int	last_exit;

// // 	i = 0;
// // 	last_exit = 0;
// // 	while (i < edata->num_cmds)
// // 	{
// // 		waitpid(edata->pid[i], &status, 0);
// // 		if (WIFEXITED(status))
// // 			last_exit = WEXITSTATUS(status);
// // 		i++;
// // 	}
// // 	edata->status = last_exit;
// // }

// void pipex(t_args *args, t_env *env_list)
// {
//     t_pipe pro;

//     // if (cmd->append)
// 	// 	ft_here_doc(argc, argv[2]);
// 	if (args->pipe)
// 		ft_create_process(args, env_list, pro);
// 	pro.pid = malloc(sizeof(pid_t) * (args->pipe));
// 	// if (!pro.pid)
// 		// return (free(pro.pid),
// 		// 	ft_error_exit("[Error] Memory allocation failed!\n"), 1);
// 	// ft_wait_children(&edata);
// 	// if (edata.pid != 0)
// 	// 	free (edata.pid);
// 	// return (edata.status);
// }


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
	ft_exec(args, env_list);
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
	ft_exec(args, env_list);
}

void	middle_child(t_args *args, t_env *env_list, t_pipe pro)
{
	close(pro.prev[1]);
	dup2(pro.prev[0], STDIN_FILENO);
	close(pro.prev[0]);
	dup2(pro.next[1], STDOUT_FILENO);
	close(pro.next[1]);
	close(pro.next[0]);
	ft_exec(args, env_list);
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
	ft_exec(args, env_list);
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


void pipex(t_args *args, t_env *env_list)
{
	t_pipe pro;
	t_cmd *current;
	t_args temp;
	int i;

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
		pro.pid[i] = fork();
		if (pro.pid[i] == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pro.pid[i] == 0)
			child_process(&temp, env_list, pro, i);
		close_pipe(pro.prev);
		update_pipe(pro.prev, pro.next);
		i++;
		current = current->next;
	}
	close_pipe(pro.prev);
	while (wait(NULL) > 0);
	free(pro.pid);
}

// void pipex(t_args *args, t_env *env_list)
// {
// 	int		pipefd[2];
// 	int		prev_fd;
// 	pid_t	pid;
// 	t_cmd	*current;
// 	t_args	temp;

// 	prev_fd = -1;
// 	current = args->cmd;
// 	while (current)
// 	{
// 		if (current->next && pipe(pipefd) == -1)
// 		{
// 			perror("pipe");
// 			exit(EXIT_FAILURE);
// 		}
// 		pid = fork();
// 		if (pid == -1)
// 		{
// 			perror("fork");
// 			exit(EXIT_FAILURE);
// 		}
// 		if (pid == 0)//child process
// 		{
// 			if (prev_fd != -1)
// 			{
// 				dup2(prev_fd, STDIN_FILENO);
// 				close(prev_fd);
// 			}
// 			if (current->next)
// 			{
// 				close(pipefd[0]);//close read end
// 				dup2(pipefd[1], STDOUT_FILENO);
// 				close(pipefd[1]);
// 			}
// 			ft_memset(&temp, 0, sizeof(t_args));
// 			temp.cmd = current;
// 			ft_exec(&temp, env_list);
// 			exit(EXIT_SUCCESS);
// 		}
// 		//parent process
// 		if (prev_fd != -1)
// 			close(prev_fd);
// 		if (current->next)
// 		{
// 			close(pipefd[1]);
// 			prev_fd = pipefd[0];
// 		}
// 		current = current->next;
// 	}
// 	while (wait(NULL) > 0);
// }
