/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:39:55 by tboulogn          #+#    #+#             */
/*   Updated: 2025/04/15 17:21:41 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*extract_word(char *input, int *i)
{
	int		start;
	char	quote;

	while (input[*i] && is_whitespace(input[*i]))
		(*i)++;
	start = *i;
	quote = 0;
	while (input[*i] && (quote || (!is_whitespace(input[*i])
				&& !is_special_char(input[*i]))))
	{
		if (input[*i] == '"' || input[*i] == '\'')
		{
			if (quote == 0)
				quote = input[*i];
			else if (quote == input[*i])
				quote = 0;
		}
		if (is_special_char(input[*i]) && !quote)
			break ;
		(*i)++;
	}
	return (ft_strndup(input + start, *i - start));
}

int	define_tokens(t_token **tokens, char *str, int i)
{
	if (str[i] == '|')
		return (add_token(tokens, "|", PIPE), 1);
	else if (str[i] == '>')
	{
		if (str[i + 1] == '>')
			return (add_token(tokens, ">>", APPEND), 2);
		else
			return (add_token(tokens, ">", REDIR_OUT), 1);
	}
	else if (str[i] == '<')
	{
		if (str[i + 1] == '<')
			return (add_token(tokens, "<<", HEREDOC), 2);
		else
			return (add_token(tokens, "<", REDIR_IN), 1);
	}
	return (0);
}

int	count_char(const char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

char	*ft_strdup_exept(const char *s, char c)
{
	size_t	len;
	char	*new_str;
	int		c_count;
	int		i;
	int		j;

	i = 0;
	c_count = count_char(s, c);
	len = ft_strlen(s) - c_count;
	new_str = malloc(len + 1 * sizeof(char));
	if (!new_str)
		return (NULL);
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			new_str[j] = s[i];
			j++;
		}
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}
