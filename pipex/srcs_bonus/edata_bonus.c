/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edata_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 08:33:43 by ryada             #+#    #+#             */
/*   Updated: 2025/03/12 13:12:11 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

t_edata	ft_init_edata(int argc, char **argv)
{
	t_edata	edata;

	edata.status = 0;
	edata.current_cmd = NULL;
	edata.pid = NULL;
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		edata.here_doc = 1;
		edata.num_cmds = 2;
	}
	else
	{
		edata.here_doc = 0;
		edata.num_cmds = argc -3;
	}
	return (edata);
}

void	ft_close_pipe(int *pipe)
{
	if (pipe[0] != -1)
		close(pipe[0]);
	if (pipe[1] != -1)
		close(pipe[1]);
}

void	ft_update_pipe(int *prev, int *next)
{
	prev[0] = next[0];
	prev[1] = next[1];
}
