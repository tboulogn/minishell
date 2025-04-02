/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:06:31 by tboulogn          #+#    #+#             */
/*   Updated: 2025/04/01 17:36:44 by tboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redirect_and_close(int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) == -1)
	{
		perror("dup2");
		close(old_fd);
		return (-1);
	}
	return (close(old_fd));
}

int	is_number(const char *str)
{
	if (!str)
		return (0);
	if (*str == '+' || *str == '-')
		str++;
	while(*str)
	{
		if (!isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

long long	ft_atoll(const char *str)
{
	int	sign;
	int	result;

	sign = 1;
	result = 0;
	while((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str++ == '-')
			sign = -sign;
	}
	while (*str && isdigit(*str))
		result = result * 10 + (*str++ - '0');
	return (result * sign);
}