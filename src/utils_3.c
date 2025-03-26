/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:44:43 by tboulogn          #+#    #+#             */
/*   Updated: 2025/03/26 14:17:16 by tboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_itoa(int nb)
{
	long	nbr;
	char	*str;
	int		i;

	nbr = nb;
	i = get_len(nbr);
	str = ft_secure_malloc((i + 1) * sizeof(char));
	str[i] = '\0';
	if (nbr == 0)
	{
		str[0] = 48;
		return(str);
	}
	if (nbr < 0)
	{
		str[0] = '-';
		nbr = -nbr;
	}
	while (nb > 0)
	{
		str[--i] = (nb % 10) + 48;
		nb = nb / 10;
	}
	return (str);
}