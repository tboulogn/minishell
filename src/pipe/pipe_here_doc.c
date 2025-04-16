/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:18:11 by ryada             #+#    #+#             */
/*   Updated: 2025/04/15 17:38:44 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_here_doc_in(t_args *args, t_cmd *current)
{
	int	j;
	int	hd_fd;

	j = 0;
	while (args->limiter[j])
	{
		hd_fd = ft_here_doc(args->limiter[j]);
		current->here_doc_fd = hd_fd;
		j++;
	}
}

int	prepare_here_doc(t_args *args, t_cmd *current)
{
	int	j;
	int	fd;

	if (args->limiter && args->cmd_count == 0)
	{
		j = 0;
		while (args->limiter[j])
		{
			fd = ft_here_doc(args->limiter[j]);
			close(fd);
			j++;
		}
	}
	if (args->limiter)
	{
		set_here_doc_in(args, current);
		return (1);
	}
	return (0);
}

void	ft_handle_here_doc_child(int *pipe_fd, char *limiter)
{
	char	*line;

	close(pipe_fd[0]);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
			&& line[ft_strlen(limiter)] == '\n')
		{
			free(line);
			break ;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		free(line);
	}
	close(pipe_fd[1]);
	exit(EXIT_SUCCESS);
}

int	ft_here_doc(char *limiter)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		status;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		ft_handle_here_doc_child(pipe_fd, limiter);
	else
	{
		close(pipe_fd[1]);
		waitpid(pid, &status, 0);
		return (pipe_fd[0]);
	}
	return (-1);
}
