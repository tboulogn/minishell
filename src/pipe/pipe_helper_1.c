/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_helper_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:31:13 by ryada             #+#    #+#             */
/*   Updated: 2025/04/15 17:41:50 by ryada            ###   ########.fr       */
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

void	close_parent_pipes(t_pipe *pro)
{
	if (pro->prev[0] != -1)
		close(pro->prev[0]);
	if (pro->prev[1] != -1)
		close(pro->prev[1]);
}

void	close_child_pipes(t_pipe *pro)
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
