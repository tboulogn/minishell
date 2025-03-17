/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:34:18 by ryada             #+#    #+#             */
/*   Updated: 2025/03/12 16:52:00 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_exec(char *cmd, char **envp)
{
	char	**cmd_tab;
	char	*cmd_path;

	cmd_tab = ft_split(cmd, ' ');
	if (!cmd_tab || !cmd_tab[0])
		ft_error_handler(1, cmd_tab, NULL);
	if (ft_strchr(cmd_tab[0], '/'))
		cmd_path = ft_strdup(cmd_tab[0]);
	else
		cmd_path = ft_get_path(cmd_tab[0], envp);
	if (!cmd_path)
		ft_error_handler(2, cmd_tab, cmd_path);
	if (execve(cmd_path, cmd_tab, envp) == -1)
		ft_error_handler(3, cmd_tab, cmd_path);
	free(cmd_path);
	ft_free_tab(cmd_tab);
}

void	ft_first_child(char **argv, int *pipe_fd, char **envp)
{
	int	fd;

	fd = ft_open_file(argv[1], 0);
	if (fd < 0)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	ft_exec(argv[2], envp);
}

void	ft_second_child(char **argv, int *pipe_fd, char **envp)
{
	int	fd;

	fd = ft_open_file(argv[4], 1);
	if (fd < 0)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	ft_exec(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		status;
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (argc != 5)
		return (ft_putstr_fd("[Error] Incorrect argument number!\n", 2), 1);
	if (pipe(pipe_fd) == -1)
		return (ft_putstr_fd("[Error] Pipe creation failed!\n", 2), 1);
	pid1 = fork();
	if (pid1 == -1)
		return (ft_putstr_fd("[Error] Fork failed!\n", 2), 1);
	if (pid1 == 0)
		ft_first_child(argv, pipe_fd, envp);
	close(pipe_fd[1]);
	pid2 = fork();
	if (pid2 == -1)
		return (ft_putstr_fd("[Error] Fork failed!\n", 2), 1);
	if (pid2 == 0)
		ft_second_child(argv, pipe_fd, envp);
	close(pipe_fd[0]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	return (WEXITSTATUS(status));
}
