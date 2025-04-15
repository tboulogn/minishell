/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_helper_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:31:13 by ryada             #+#    #+#             */
/*   Updated: 2025/04/15 17:41:45 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	read_files(t_cmd *cmd, int fd, int type)
{
	if (type == 1)
	{
		fd = open(cmd->infile, O_RDONLY);
		if (fd < 0)
			perror(cmd->infile);
		redirect_and_close(fd, STDIN_FILENO);
	}
	else if (type == 2)
	{
		fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			perror(cmd->outfile);
		redirect_and_close(fd, STDOUT_FILENO);
	}
	else if (type == 3)
	{
		fd = open(cmd->append_outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
			perror(cmd->append_outfile);
		redirect_and_close(fd, STDOUT_FILENO);
	}
}

int	no_files(t_cmd *cmd)
{
	if (!cmd->infile && !cmd->outfile && !cmd->append_outfile)
		return (1);
	return (0);
}

void	init_temp_args(t_args *temp, t_cmd *current, int cmd_count, int i)
{
	ft_memset(temp, 0, sizeof(t_args));
	temp->cmd = current;
	temp->cmd_count = cmd_count;
	temp->index = i;
}

void	close_and_update(t_pipe *pro)
{
	close_parent_pipes(pro);
	update_pipe(pro->prev, pro->next);
}
