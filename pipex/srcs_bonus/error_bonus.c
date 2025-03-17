/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:55:21 by ryada             #+#    #+#             */
/*   Updated: 2025/03/12 17:06:41 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	ft_error_exit(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit(1);
}

void	ft_safe_print_error(const char *msg, const char *arg)
{
	write(2, msg, ft_strlen(msg));
	if (arg)
	{
		write(2, arg, ft_strlen(arg));
		write(2, "\n", 1);
	}
}

void	ft_cmd_error_handler(int type, char **cmd_tab,
		char *cmd_path, pid_t *pid)
{
	if (type == 1)
		ft_safe_print_error("[Error] Command parsing failed!\n", NULL);
	else if (type == 2)
		ft_safe_print_error("[Error] Command not found! : ", cmd_tab[0]);
	else if (type == 3)
		ft_safe_print_error("[Error] Command execution failed!: ", cmd_tab[0]);
	if (cmd_path && cmd_path != cmd_tab[0])
		free(cmd_path);
	ft_free_tab(cmd_tab);
	if (type == 2)
	{
		free(pid);
		exit (127);
	}
	else
	{
		free(pid);
		exit (EXIT_FAILURE);
	}
}

void	ft_general_error_handler(t_edata edata, int type)
{
	free(edata.pid);
	if (type == 1)
		ft_error_exit("[Error] Pipe creation failed!\n");
	else if (type == 2)
		ft_error_exit("[Error] Fork creation failed!\n");
	else if (type == 3)
		ft_error_exit("[Error] Memory allocation failed!\n");
}
