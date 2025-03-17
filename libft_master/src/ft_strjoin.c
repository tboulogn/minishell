/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 10:22:40 by tboulogn          #+#    #+#             */
/*   Updated: 2025/02/05 16:09:32 by tboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	size_t	i;
	char	*s3;

	if (!s1 && !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	s3 = malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (!s3)
		return (NULL);
	i = 0;
	while (s1 && *s1)
		s3[i++] = *s1++;
	while (s2 && *s2)
		s3[i++] = *s2++;
	s3[i] = '\0';
	return (s3);
}
