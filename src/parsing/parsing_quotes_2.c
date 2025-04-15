/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing _quotes_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:39:55 by tboulogn          #+#    #+#             */
/*   Updated: 2025/04/15 17:20:12 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_inside_sigle_quote(const char *str, int dollar_index)
{
	bool	s_open;
	bool	d_open;
	int		i;

	s_open = false;
	d_open = false;
	i = 0;
	while (i < dollar_index)
	{
		if (str[i] == '\'' && !d_open)
			s_open = !s_open;
		else if (str[i] == '"' && !s_open)
			d_open = !d_open;
		i++;
	}
	return (s_open);
}

char	*update_quotes_and_clean(char *content, bool *sq, bool *dq)
{
	quotes_update(content, sq, dq);
	return (clean_word_quotes(content));
}

char	*expand_if_needed(char *cleaned, t_env *env_list)
{
	char	*expanded;
	int		dollar_pos;

	if (ft_strchr(cleaned, '$'))
	{
		dollar_pos = find_char_pos(cleaned, '$');
		if (dollar_pos >= 0 && !is_inside_sigle_quote(cleaned, dollar_pos))
		{
			expanded = expand_vars(cleaned, env_list, 0);
			free(cleaned);
			return (expanded);
		}
	}
	return (cleaned);
}
