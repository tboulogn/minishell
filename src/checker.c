/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:44:18 by ryada             #+#    #+#             */
/*   Updated: 2025/03/21 17:34:30 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int check_syntax_error(t_token *tokens)
{
    t_token *current;

    current = tokens;
    if (!current)
        return (1);
    if (current->type == PIPE)
    {
        printf("Syntax error: pipe at start\n\n");
        return (0);
    }
    while (current)
    {
        if ((current->type == PIPE) && (!current->next || current->next->type != WORD))
        {
            printf("Syntax error: invalid pipe placement\n\n");
            return (0);
        }
        else if ((current->type == REDIR_IN || current->type == REDIR_OUT || current->type == APPEND || current->type == HEREDOC))
        {
            if (!current->next || current->next->type != WORD)
            {
                printf("Syntax error: redirection with no target\n\n");
                return (0);
            }
        }
        current = current->next;
    }
    return (1);
}
//need to check the place of limiter as well, meaning check the pipe placement related to this too