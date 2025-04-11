/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:18:46 by tboulogn          #+#    #+#             */
/*   Updated: 2025/04/11 08:59:47 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exit(t_args *args, t_env **env)
{
	long long	code;

	printf("exit\n");
	if (!args->cmd->cmd_tab[1])
	{
		free_cmd_list(args);
		free_env_list(*env);
		exit(0);
	}
	if (!is_number(args->cmd->cmd_tab[1]))
	{
		printf("minishell: exit: %s: numeric argument required\n",
			args->cmd->cmd_tab[1]);
		free_cmd_list(args);
		free_env_list(*env);
		exit (2);
	}
	if (args->cmd->cmd_tab[2])
		return (printf("minishell: exit: too many arguments\n"), 1);
	code = ft_atoll(args->cmd->cmd_tab[1]);
	free_cmd_list(args);
	free_env_list(*env);
	exit((unsigned char)code);
}
