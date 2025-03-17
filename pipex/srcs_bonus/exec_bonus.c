/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:50:57 by ryada             #+#    #+#             */
/*   Updated: 2025/03/12 16:59:48 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	ft_exec(char *cmd, char **envp, pid_t *pid)
{
	char	**cmd_tab;
	char	*cmd_path;

	cmd_tab = ft_split(cmd, ' ');
	if (!cmd_tab || !cmd_tab[0])
		ft_cmd_error_handler(1, cmd_tab, NULL, pid);
	if (ft_strchr(cmd_tab[0], '/'))
		cmd_path = ft_strdup(cmd_tab[0]);
	else
		cmd_path = ft_get_path(cmd_tab[0], envp);
	if (!cmd_path)
		ft_cmd_error_handler(2, cmd_tab, cmd_path, pid);
	if (execve(cmd_path, cmd_tab, envp) == -1)
		ft_cmd_error_handler(3, cmd_tab, cmd_path, pid);
	free(cmd_path);
	ft_free_tab(cmd_tab);
}
