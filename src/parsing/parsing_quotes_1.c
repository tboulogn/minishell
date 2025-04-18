/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quotes_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:39:55 by tboulogn          #+#    #+#             */
/*   Updated: 2025/04/18 11:39:54 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handel_quoates(bool *open, bool *has_content,
			bool *has, bool other_quote_open)
{
	if (!other_quote_open)
	{
		if (*open && *has_content)
			*has = true;
		*open = !*open;
		if (!*open)
			*has_content = false;
	}
}

void	update_content(bool *s_open, bool *d_open,
			bool *s_content, bool *d_content)
{
	if (s_open)
		*s_content = true;
	if (d_open)
		*d_content = true;
}

char	*clean_word_quotes(const char *str)
{
	char	*tmp;
	char	*cleaned;

	if (!str)
		return (NULL);
	tmp = ft_strdup_exept(str, '\'');
	cleaned = ft_strdup_exept(tmp, '"');
	free(tmp);
	return (cleaned);
}

void	update_open_bool(bool *s_open, bool	*d_open,
			bool *s_content, bool *d_content)
{
	if (*s_open)
		*s_content = true;
	if (*d_open)
		*d_content = true;
}

void	quotes_update(const char *str, bool *has_sq, bool *has_dq)
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
		if ((s_open && str[i] != '\'') || (d_open && str[i] != '"'))
			update_open_bool(&s_open, &d_open, &s_content, &d_content);
		i++;
	}
}
