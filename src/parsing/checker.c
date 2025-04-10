/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:44:18 by ryada             #+#    #+#             */
/*   Updated: 2025/04/10 15:49:27 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	quotes_closed_str(const char *str, bool *has_sq, bool *has_dq)
{
	bool	s_open;
	bool	d_open;
	bool	s_content;
	bool	d_content;
	int		i;

	s_open = false;
	d_open = false;
	s_content = false;
	d_content = false;
	*has_sq = false;
	*has_dq = false;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !d_open)
			handel_quoates(&s_open, &s_content, has_sq, d_open);
		else if (str[i] == '"' && !s_open)
			handel_quoates(&d_open, &d_content, has_dq, s_open);
		update_content(&s_open, &d_open, &s_content, &d_content);
		i++;
	}
	return (!s_open && !d_open);
}

void	syntax_error_message(int type)
{
	ft_putstr_fd("Syntax error:", 2);
	if (type == -1)
		ft_putstr_fd(" pipe at start\n", 2);
	else if (type == -2)
		ft_putstr_fd(" invalid pipe placement\n", 2);
	else if (type == -3)
		ft_putstr_fd(" redirection with no target\n", 2);
}

int	check_syntax_error(t_token *tokens)
{
	t_token	*current;
	bool has_sq;
    bool has_dq;

	current = tokens;
	if (!current)
		return (1);
	if (current->type == PIPE)
		return (syntax_error_message(-1), 0);
	while (current)
	{
		if (!quotes_closed_str(current->value, &has_sq, &has_dq)) // <== ADD THIS
        {
            ft_putstr_fd("Syntax error: unclosed quotes\n", 2);   // <== Nice error
            return (0);
        }
		if ((current->type == PIPE)
			&& (!current->next || current->next->type != WORD))
			// || (current->type == REDIR_IN && current->next->next->type != PIPE))
			return (syntax_error_message(-2), 0);
		else if ((current->type == REDIR_IN || current->type == REDIR_OUT
				|| current->type == APPEND || current->type == HEREDOC)
			&& (!current->next || current->next->type != WORD))
			return (syntax_error_message(-3), 0);
		current = current->next;
	}
	return (1);
}
