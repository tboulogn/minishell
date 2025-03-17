/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 09:26:44 by tboulogn          #+#    #+#             */
/*   Updated: 2025/02/05 16:09:59 by tboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	int				last_occ;
	unsigned char	uc;

	i = 0;
	last_occ = -1;
	uc = (unsigned char)c;
	while (s[i] != '\0')
	{
		if ((unsigned char)s[i] == uc)
			last_occ = i;
		i++;
	}
	if (uc == '\0')
		return ((char *)&s[i]);
	if (last_occ != -1)
		return ((char *)&s[last_occ]);
	return (NULL);
}
