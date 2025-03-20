/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:20:17 by tboulogn          #+#    #+#             */
/*   Updated: 2025/03/20 14:50:04 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void	*ft_secure_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (!ret)
		ft_putstr_fd("Error with malloc.", 2);
	return (ret);
}

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t');
}

int is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

char	*ft_strndup(const char *s, size_t len)
{
	size_t	i;
	char	*new_str;

	new_str = ft_secure_malloc(sizeof(char) * (len + 1));
	i = 0;
	while (i < len && s[i])
	{
		new_str[i] = s[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

char	*ft_strjoin_three(char const *s1, char const *s2, const char *s3)
{
	size_t	len_s1;
	size_t	len_s2;
	size_t	len_s3;
	size_t	i;
	char	*new_str;

	if (!s1 || !s2 || !s3)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	len_s3 = ft_strlen(s3);
	s3 = ft_secure_malloc((len_s1 + len_s2 + len_s3 + 1) * sizeof(char));
	i = 0;
	while (*s1)
		new_str[i++] = *s1++;
	while (*s2)
		new_str[i++] = *s2++;
	while(*s3)
		new_str[i++] = *s3++;
	new_str[i] = '\0';
	return (new_str);
}
