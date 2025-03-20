/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tab.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 10:14:59 by tboulogn          #+#    #+#             */
/*   Updated: 2025/03/20 13:16:15 by tboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_env(char **envp)
{
	int	count;
	
	count = 0;
	while (envp[count])
		count++;
	return (count);
}

char **copy_env(char **envp)
{
	int		i;
	int		env_count;
	char	**env_copy;

	env_count = count_env(envp);
	env_copy = ft_secure_malloc((env_count + 1) * sizeof(char *));
	i = 0;
	while (envp[i])
	{
		env_copy[i] = ft_strdup(envp[i]);
		if (!env_copy[i])
		{
			while (i--)
				free(env_copy[i]);
			return (free(env_copy), NULL);
		}
		i++;
	}
	env_copy[i] = NULL;
	return (env_copy);
}

int	find_env_var(char **env, const char *key)
{
	int	i;
	int	len;
	
	len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, len) == 0 && env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char *get_env_value(char **env, const char *key)
{
	int	i;
	int	len;

	len = ft_strlen(key);
	i = find_env_var(env, key);
	if (i != -1)
		return (env[i] + len + 1);
	return (NULL);
}

char		**set_env_value(char **env, const char *key, const char *new_value)
{
	int 	i;
	int		env_count;
	char	*new_entry;
	char	**new_envp;
	
	if (!env || !key || !new_value)
		return(env);
	new_entry = ft_strjoin_three(key, "=", new_value);
	i = find_env_var(env, key);
	if (i >= 0)
	{
		free(env[i]);
		env[i] = new_entry;
		return (env);
	}
	env_count = count_env(env);
	new_envp = ft_secure_malloc((env_count + 2) * sizeof(char *));
	i = -1;
	while (i++ < env_count)
		new_envp[i] = env[i];
	new_envp[env_count] = new_entry;
	new_envp[env_count + 1] = NULL;
	return (free(env), new_envp);
}
