/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:18:46 by tboulogn          #+#    #+#             */
/*   Updated: 2025/04/01 17:41:58 by tboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exit(t_args *args)
{
	long long	code;
	
	printf("exit\n");
	if (!args->cmd->cmd_tab[1])
		exit(0);
	if (!is_number(args->cmd->cmd_tab[1]))
	{
		printf("minishell: exit: %s: numeric argument required\n", args->cmd->cmd_tab[1]);
		exit (255);
	}
	if (args->cmd->cmd_tab[2])
	{
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	code = ft_atoll(args->cmd->cmd_tab[1]);
	exit((unsigned char)code);
}
