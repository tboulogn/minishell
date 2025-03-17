/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:01:11 by tboulogn          #+#    #+#             */
/*   Updated: 2025/02/05 16:08:44 by tboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*new_str;

	len = ft_strlen(s);
	new_str = malloc(len + 1 * sizeof(char));
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, s, len + 1);
	return (new_str);
}
