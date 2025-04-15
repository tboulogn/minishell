/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:42:02 by ryada             #+#    #+#             */
/*   Updated: 2025/04/15 16:21:38 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_cmd_path(char *path)
{
	struct stat	s;

	if (stat(path, &s) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (127);
	}
	if (S_ISDIR(s.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": Not a directory\n", 2);
		return (127);
	}
	if (access(path, X_OK) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return (126);
	}
	return (0);
}

void	error_cmd_not_found(t_args *args, t_env *env_list,
			t_pipe *pro, char **envp_arr)
{
	char	**cmd_tab;

	cmd_tab = args->cmd->cmd_tab;
	if (envp_arr)
		free_env_array(envp_arr);
	if (cmd_tab && cmd_tab[0])
	{
		ft_putstr_fd(cmd_tab[0], 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else
		ft_putstr_fd(": command not found\n", 2);
	free_ereaser(args, env_list, pro);
	exit(127);
}
