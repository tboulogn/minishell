/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:00:10 by tboulogn          #+#    #+#             */
/*   Updated: 2025/02/05 17:39:22 by tboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_check_strtrim(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		i;
	int		j;
	int		len;
	int		istr;

	i = 0;
	if (!s1 || s1[0] == '\0')
	{
		return (ft_strdup("\0"));
	}
	j = ft_strlen(s1) - 1;
	while (s1[i] && ft_check_strtrim(set, s1[i]) == 1)
		i++;
	while (s1[j] && ft_check_strtrim(set, s1[j]) == 1 && j > i)
		j--;
	len = j - i + 1;
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	istr = 0;
	while (i < j + 1)
		str[istr++] = s1[i++];
	str[istr] = '\0';
	return (str);
}
