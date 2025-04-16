/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:42:02 by ryada             #+#    #+#             */
/*   Updated: 2025/04/15 16:20:21 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_getenv_from_list(char *key, t_env *env_list)
{
	while (env_list)
	{
		if (ft_strncmp(env_list->key, key, ft_strlen(key) + 1) == 0)
			return (env_list->value);
		env_list = env_list->next;
	}
	return (NULL);
}

char	*ft_check_exec_path(char *dir, char *cmd)
{
	char	*path;
	char	*exec;

	path = ft_strjoin(dir, "/");
	if (!path)
		return (NULL);
	exec = ft_strjoin(path, cmd);
	free(path);
	if (!exec)
		return (NULL);
	if (!access(exec, F_OK) && !access(exec, X_OK))
		return (exec);
	free(exec);
	return (NULL);
}

char	*ft_get_path(char *cmd, t_env *env_list)
{
	int		i;
	char	*exec;
	char	*env_path;
	char	**all_paths;

	env_path = ft_getenv_from_list("PATH", env_list);
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
		i++;
	}
	ft_free_tab(all_paths);
	return (exec);
}

char	**env_list_to_envp(t_env *env)
{
	int		count;
	char	**envp;
	int		i;

	i = 0;
	count = count_env_line(env);
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	while (env)
	{
		if (env->value)
			envp[i] = ft_strjoin_3(env->key, "=", env->value);
		else
			envp[i] = ft_strjoin(env->key, "=");
		i++;
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

char	*define_cmd_path(char **cmd_tab, t_env *env)
{
	if (ft_strchr(cmd_tab[0], '/'))
		return (ft_strdup(cmd_tab[0]));
	return (ft_get_path(cmd_tab[0], env));
}
