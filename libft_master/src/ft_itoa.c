/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:54:49 by tboulogn          #+#    #+#             */
/*   Updated: 2025/02/05 16:06:47 by tboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrev(char *str)
{
	int	i;
	int	len;
	int	tmp;

	i = 0;
	len = ft_strlen(str) - 1;
	while (i < len)
	{
		tmp = str[i];
		str[i] = str[len];
		str[len] = tmp;
		i++;
		len--;
	}
	return (str);
}

int	ft_intlen(int n)
{
	int		len;

	len = 1;
	if (n < 0)
	{
		len++;
		n = -n;
	}
	while (n >= 10)
	{
		n /= 10;
		len++;
	}
	return (len);
}

int	ft_sign(int n)
{
	if (n < 0)
		return (-1);
	else
		return (1);
}

char	*ft_itoa(int n)
{
	int		i;
	int		sign;
	char	*str;

	i = 0;
	sign = ft_sign(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	str = malloc((ft_intlen(n) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	if (n == 0)
		str[i++] = '0';
	if (n < 0)
		n = -n;
	while (n != 0)
	{
		str[i++] = (n % 10) + '0';
		n /= 10;
	}
	if (sign == -1)
		str[i++] = '-';
	str[i] = '\0';
	return (ft_strrev(str));
}
