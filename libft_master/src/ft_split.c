/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 08:49:38 by tboulogn          #+#    #+#             */
/*   Updated: 2025/02/05 16:08:34 by tboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static size_t	is_in_charset(char c, char charset)
{
	return (c == charset);
}

static size_t	count_word(char const *s, char charset)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s && is_in_charset(*s, charset))
			s++;
		if (*s && !is_in_charset(*s, charset))
		{
			count++;
			while (*s && !is_in_charset(*s, charset))
				s++;
		}
	}
	return (count);
}

static char	*malloc_word(char const *s, char charset)
{
	size_t	i;
	char	*word;

	i = 0;
	while (s[i] && !is_in_charset(s[i], charset))
		i++;
	word = malloc(sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (s[i] && !is_in_charset(s[i], charset))
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static void	ft_free(char **split, size_t alloc)
{
	size_t	i;

	i = 0;
	while (i < alloc)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	char	**split;

	i = 0;
	split = (char **)malloc(sizeof(char *) * (count_word(s, c) + 1));
	if (!split)
		return (NULL);
	while (*s)
	{
		while (*s && is_in_charset(*s, c))
			s++;
		if (*s && !is_in_charset(*s, c))
		{
			split[i] = malloc_word(s, c);
			if (!split[i])
			{
				ft_free(split, i);
				return (NULL);
			}
			i++;
			while (*s && !is_in_charset(*s, c))
				s++;
		}
	}
	return (split[i] = NULL, split);
}
