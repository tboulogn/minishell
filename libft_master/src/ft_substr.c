/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 09:39:47 by tboulogn          #+#    #+#             */
/*   Updated: 2025/02/05 16:10:07 by tboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_str;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		new_str = malloc(1);
		if (!new_str)
			return (NULL);
		new_str[0] = '\0';
		return (new_str);
	}
	if (len > s_len - start)
		len = s_len - start;
	new_str = malloc(len + 1 * sizeof(char));
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, &s[start], len + 1);
	return (new_str);
}
