/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:39:55 by tboulogn          #+#    #+#             */
/*   Updated: 2025/04/15 17:23:09 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*tokenize(char *input)
{
	t_token	*tokens;
	int		i;
	char	*word;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		while (input[i] && is_whitespace(input[i]))
			i++;
		i += define_tokens(&tokens, input, i);
		if (input[i])
		{
			word = extract_word(input, &i);
			add_token(&tokens, word, WORD);
			free(word);
		}
	}
	return (tokens);
}

void	add_token(t_token **tokens, char *value, t_token_type type)
{
	t_token	*new;
	t_token	*tmp;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		return ;
	new->value = ft_strdup(value);
	new->type = type;
	new->next = NULL;
	new->prev = NULL;
	if (!*tokens)
		*tokens = new;
	else
	{
		tmp = *tokens;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
}

t_args	*create_new_args(void)
{
	t_args	*new_args;

	new_args = ft_calloc(1, sizeof(t_args));
	if (!new_args)
		return (NULL);
	new_args->cmd_count = 0;
	new_args->limiter = NULL;
	new_args->here_doc_count = 0;
	new_args->pipe = 0;
	new_args->cmd = NULL;
	new_args->index = 0;
	return (new_args);
}

void	add_cmd_back(t_args *args, t_cmd *new_cmd)
{
	t_cmd	*last;

	if (!args || !new_cmd)
		return ;
	new_cmd->next = NULL;
	new_cmd->prev = NULL;
	new_cmd->here_doc_fd = -1;
	new_cmd->infile = NULL;
	new_cmd->outfile = NULL;
	new_cmd->append_outfile = NULL;
	if (!args->cmd)
	{
		args->cmd = new_cmd;
		return ;
	}
	last = args->cmd;
	while (last->next)
		last = last->next;
	last->next = new_cmd;
	new_cmd->prev = last;
}
