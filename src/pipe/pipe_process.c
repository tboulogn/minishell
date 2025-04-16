/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:31:13 by ryada             #+#    #+#             */
/*   Updated: 2025/04/15 17:40:49 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	single_child(t_args *args, t_cmd *cmd, t_env *env_list, t_pipe pro)
{
	int	fd_in;
	int	fd_out;

	fd_in = 0;
	fd_out = 0;
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

	fd = 0;
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
	int	fd_in;
	int	fd_out;

	fd_in = 0;
	fd_out = 0;
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
	int	fd_in;
	int	fd_out;

	fd_in = 0;
	fd_out = 0;
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

void	child_process(t_args *temp, t_cmd *cmd, t_env *env_list, t_pipe pro)
{
	if (cmd->here_doc_fd != -1)
	{
		dup2(cmd->here_doc_fd, STDIN_FILENO);
		close(cmd->here_doc_fd);
	}
	if (temp->index == 0)
	{
		if (temp->cmd_count == 1)
			single_child(temp, cmd, env_list, pro);
		else
			first_child(temp, cmd, env_list, pro);
	}
	else if (temp->index == temp->cmd_count -1)
		last_child(temp, cmd, env_list, pro);
	else
		middle_child(temp, cmd, env_list, pro);
	exit(EXIT_SUCCESS);
}
