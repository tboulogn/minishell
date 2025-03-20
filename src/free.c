/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:15:32 by tboulogn          #+#    #+#             */
/*   Updated: 2025/03/20 16:56:08 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_token(t_token *tokens)
{
	t_token *tmp;

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
	t_args	*tmp;
	int		i;

	while (args)
	{
		tmp = args->next;
		if (args->cmds)
		{
			i = 0;
			while (args->cmds[i])
			{
				free(args->cmds[i]);
				i++;
			}
			free(args->cmds);
		}
		if (args->infile)
			free(args->infile);
		if  (args->outfile)
			free(args->outfile);
	free(args);
	args = tmp;
	}
}
