/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:44:18 by ryada             #+#    #+#             */
/*   Updated: 2025/04/09 17:25:11 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

	current = tokens;
	if (!current)
		return (1);
	if (current->type == PIPE)
		return (syntax_error_message(-1), 0);
	while (current)
	{
		if (((current->type == PIPE)
			&& (!current->next || current->next->type != WORD))
			|| (current->type == REDIR_IN && current->next->next->type != PIPE))
			return (syntax_error_message(-2), 0);
		else if ((current->type == REDIR_IN || current->type == REDIR_OUT
				|| current->type == APPEND || current->type == HEREDOC)
			&& (!current->next || current->next->type != WORD))
			return (syntax_error_message(-3), 0);
		current = current->next;
	}
	return (1);
}
