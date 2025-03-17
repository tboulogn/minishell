/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:33:22 by ryada             #+#    #+#             */
/*   Updated: 2025/03/12 12:04:44 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	ft_child_process(char **argv, char **envp, t_edata edata, int i)
{
	if (i == 0)
		ft_first_child(argv, envp, edata);
	else if (i == edata.num_cmds - 1)
		ft_last_child(argv, envp, edata);
	else
		ft_middle_child(envp, edata);
	exit(EXIT_SUCCESS);
}

void	ft_create_process(char **argv, char **envp, t_edata edata)
{
	int	i;

	i = 0;
	edata.prev_pipe[0] = -1;
	edata.prev_pipe[1] = -1;
	while (i < edata.num_cmds)
	{
		if (pipe(edata.next_pipe) == -1)
			ft_general_error_handler(edata, 1);
		edata.current_cmd = argv[i + 2];
		edata.pid[i] = fork();
		if (edata.pid[i] == -1)
			ft_general_error_handler(edata, 2);
		if (edata.pid[i] == 0)
			ft_child_process(argv, envp, edata, i);
		ft_close_pipe(edata.prev_pipe);
		ft_update_pipe(edata.prev_pipe, edata.next_pipe);
		i++;
	}
	ft_close_pipe(edata.prev_pipe);
}

void	ft_wait_children(t_edata *edata)
{
	int	i;
	int	status;
	int	last_exit;

	i = 0;
	last_exit = 0;
	while (i < edata->num_cmds)
	{
		waitpid(edata->pid[i], &status, 0);
		if (WIFEXITED(status))
			last_exit = WEXITSTATUS(status);
		i++;
	}
	edata->status = last_exit;
}
