/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:31:10 by tboulogn          #+#    #+#             */
/*   Updated: 2025/03/21 11:09:36 by tboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_echo(t_args *args)
{
	int	i;
 	int	n_flag;

 	if (!args || !args->cmds[1])
 		return (ft_putstr_fd("\n", 1), 0);
 	i = 1;
 	n_flag = 0;
 	while (args->cmds[i] && ft_strncmp(args->cmds[i], "-n", 2) == 0)	
 	{
 		n_flag = 1;
 		i++;
 	}
 	while (args->cmds[i])
 	{
 		ft_putstr_fd(args->cmds[i], 1);
		if (args->cmds[i + 1])
		{
 			ft_putstr_fd(" ", 1);
 			i++;
 		}
	}
 	if (!n_flag)
 		ft_putstr_fd("\n", 1);
 	return (0);
}
