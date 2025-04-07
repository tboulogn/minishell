/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:15:32 by tboulogn          #+#    #+#             */
/*   Updated: 2025/04/01 15:12:17 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//everytime you finish the execution, free EVERYTHING!!

void	free_token(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		free(tokens->value);
		free(tokens);
		tokens = tmp;
	}
}

void	free_cmd_list(t_args *args)
{
	t_cmd	*tmp_cmd;
	t_cmd	*next_cmd;
	int		i;

	if (!args)
		return ;
	tmp_cmd = args->cmd;
	while (tmp_cmd)
	{
		next_cmd = tmp_cmd->next;
		if (tmp_cmd->cmd_tab)
		{
			i = 0;
			while (tmp_cmd->cmd_tab[i])
			{
				free(tmp_cmd->cmd_tab[i]);
				i++;
			}
			free(tmp_cmd->cmd_tab);
		}
		if (tmp_cmd->cmd_path)
			free(tmp_cmd->cmd_path);
		free(tmp_cmd);
		tmp_cmd = next_cmd;
	}
	// if (args->infile)
	// 	free(args->infile);
	// if (args->outfile)
	// 	free(args->outfile);
	// if (args->append_outfile)
	// 	free(args->append_outfile);
	if (args->limiter)
		free(args->limiter);
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
