/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:15:32 by tboulogn          #+#    #+#             */
/*   Updated: 2025/04/16 16:19:06 by tboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//everytime you finish the execution, free EVERYTHING!!

void	free_token(t_token *tokens)
{
	t_token	*next_token;

	while (tokens)
	{
		next_token = tokens->next;
		free(tokens->value);
		free(tokens);
		tokens = next_token;
	}
}

static void	free_one_cmd(t_cmd *cmd)
{
	int	i;

	if (!cmd)
		return ;
	if (cmd->cmd_tab)
	{
		i = 0;
		while (cmd->cmd_tab[i])
			free(cmd->cmd_tab[i++]);
		free(cmd->cmd_tab);
	}
	if (cmd->sq)
		free(cmd->sq);
	if (cmd->dq)
		free(cmd->dq);
	if (cmd->cmd_path)
		free(cmd->cmd_path);
	if (cmd->infile)
		free(cmd->infile);
	if (cmd->outfile)
		free(cmd->outfile);
	if (cmd->append_outfile)
		free(cmd->append_outfile);
	free(cmd);
}

void	free_cmd_list(t_args *args)
{
	t_cmd	*tmp_cmd;
	t_cmd	*next_cmd;

	if (!args)
		return ;
	tmp_cmd = args->cmd;
	while (tmp_cmd)
	{
		next_cmd = tmp_cmd->next;
		free_one_cmd(tmp_cmd);
		tmp_cmd = next_cmd;
	}
	free_env_array(args->limiter);
	free(args);
}

void	free_env_array(char **env_array)
{
	int	i;

	if (!env_array)
		return ;
	i = 0;
	while (env_array[i])
	{
		free(env_array[i]);
		i++;
	}
	free(env_array);
}

void	free_env_node(t_env *node)
{
	if (!node)
		return ;
	free(node->key);
	free(node->value);
	free(node);
}
