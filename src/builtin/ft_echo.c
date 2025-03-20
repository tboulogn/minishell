/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:31:10 by tboulogn          #+#    #+#             */
/*   Updated: 2025/03/20 16:15:21 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int	ft_echo(t_cmd *cmd)
// {
// 	int	i;
// 	int	n_flag;

// 	if (!cmd || !cmd->args[1])
// 		return (ft_putstr_fd("\n", 1), 0);
// 	i = 1;
// 	n_flag = 0;

// 	while (cmd->args[i] && ft_strncmp(cmd->args[i], "-n", 2) == 0)	
// 	{
// 		n_flag = 1;
// 		i++;
// 	}
// 	while (cmd->args[i])
// 	{
// 		ft_putstr_fd(cmd->args[i], 1);
// 		if (cmd->args[i + 1])
// 			ft_putstr_fd(" ", 1);
// 		i++;
// 	}
// 	if (!n_flag)
// 		ft_putstr_fd("\n", 1);
// 	return (0);
// }
