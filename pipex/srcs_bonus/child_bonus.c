/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:52:22 by ryada             #+#    #+#             */
/*   Updated: 2025/03/12 11:56:31 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	ft_first_child(char **argv, char **envp, t_edata edata)
{
	int	fd;

	close(edata.next_pipe[0]);
	if (!edata.here_doc)
	{
		fd = ft_open_file(argv[1], 2, edata.pid);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	dup2(edata.next_pipe[1], STDOUT_FILENO);
	close(edata.next_pipe[1]);
	if (edata.here_doc)
		ft_exec(argv[3], envp, edata.pid);
	else
		ft_exec(argv[2], envp, edata.pid);
}

void	ft_middle_child(char **envp, t_edata edata)
{
	close(edata.prev_pipe[1]);
	dup2(edata.prev_pipe[0], STDIN_FILENO);
	close(edata.prev_pipe[0]);
	dup2(edata.next_pipe[1], STDOUT_FILENO);
	close(edata.next_pipe[1]);
	close(edata.next_pipe[0]);
	ft_exec(edata.current_cmd, envp, edata.pid);
}

void	ft_last_child(char **argv, char **envp, t_edata edata)
{
	int	fd;
	int	argc;

	argc = ft_arg_count(argv);
	close(edata.prev_pipe[1]);
	if (!edata.here_doc)
		fd = ft_open_file(argv[argc - 1], 1, edata.pid);
	else
		fd = ft_open_file(argv[argc - 1], 0, edata.pid);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	dup2(edata.prev_pipe[0], STDIN_FILENO);
	close(edata.prev_pipe[0]);
	ft_exec(argv[argc - 2], envp, edata.pid);
}
