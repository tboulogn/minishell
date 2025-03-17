/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 08:33:43 by ryada             #+#    #+#             */
/*   Updated: 2025/03/12 12:06:14 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

char	*ft_getenv(char *key, char **envp)
{
	int		i;
	size_t	len;

	len = ft_strlen(key);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, len) == 0 && envp[i][len] == '=')
			return (envp[i] + (len + 1));
		i++;
	}
	return (NULL);
}

char	*ft_check_exec_path(char *dir, char *cmd)
{
	char	*path;
	char	*exec;

	path = ft_strjoin(dir, "/");
	exec = ft_strjoin(path, cmd);
	free(path);
	if (!access(exec, F_OK) && !access(exec, X_OK))
		return (exec);
	free(exec);
	return (NULL);
}

char	*ft_get_path(char *cmd, char **envp)
{
	int		i;
	char	*exec;
	char	*env_path;
	char	**all_paths;

	env_path = ft_getenv("PATH", envp);
	if (!env_path)
		return (NULL);
	all_paths = ft_split(env_path, ':');
	if (!all_paths)
		return (NULL);
	i = 0;
	exec = NULL;
	while (all_paths[i] && !exec)
	{
		exec = ft_check_exec_path(all_paths[i], cmd);
		if (!exec)
			free(exec);
		i++;
	}
	ft_free_tab(all_paths);
	return (exec);
}
