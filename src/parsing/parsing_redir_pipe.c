/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing _redire_pipe.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:39:55 by tboulogn          #+#    #+#             */
/*   Updated: 2025/04/15 17:17:05 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parsing_type(t_token *tokens)
{
	if (tokens->type == PIPE)
		return (1);
	else if (tokens->type == HEREDOC && tokens->next
		&& tokens->next->type == WORD)
		return (2);
	else if (tokens->type == WORD && (!tokens->prev
			|| (tokens->prev->type != REDIR_IN
				&& tokens->prev->type != REDIR_OUT
				&& tokens->prev->type != APPEND
				&& tokens->prev->type != HEREDOC)))
		return (3);
	else if (tokens->type == WORD && tokens->prev
		&& (tokens->prev->type == REDIR_IN
			|| tokens->prev->type == REDIR_OUT
			|| tokens->prev->type == APPEND))
		return (4);
	return (0);
}

void	first_limitter(char ***arr, char *line)
{
	*arr = malloc(sizeof(char *) * 2);
	if (!*arr)
		return ;
	(*arr)[0] = ft_strdup(line);
	(*arr)[1] = NULL;
	return ;
}

int	parse_pipe(t_args *args, t_cmd **current_cmd,
			t_env *env_list, t_list **word_list)
{
	if (*word_list)
	{
		*current_cmd = create_cmd_from_list(*word_list, env_list);
		if (!*current_cmd)
			return (free_cmd_list(args), 0);
		add_cmd_back(args, *current_cmd);
		args->cmd_count++;
		*word_list = NULL;
	}
	args->pipe++;
	*current_cmd = NULL;
	return (1);
}

int	parse_redir(t_args *args, t_cmd **current_cmd,
			t_env *env_list, t_list **word_list)
{
	if (!*current_cmd && *word_list)
	{
		*current_cmd = create_cmd_from_list(*word_list, env_list);
		add_cmd_back(args, *current_cmd);
		args->cmd_count++;
		*word_list = NULL;
	}
	if (!*current_cmd)
	{
		*current_cmd = ft_calloc(1, sizeof(t_cmd));
		if (!*current_cmd)
			return (0);
		(*current_cmd)->here_doc_fd = -1;
		add_cmd_back(args, *current_cmd);
		args->cmd_count++;
	}
	return (1);
}

void	parse_here_doc(t_token *tokens, t_args *args)
{
	args->here_doc_count++;
	add_malloc_line(&(args->limiter), tokens->next->value);
	tokens = tokens->next;
}
