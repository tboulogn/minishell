/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:41:31 by tboulogn          #+#    #+#             */
/*   Updated: 2025/03/19 20:05:57 by tboulogn         ###   ########.fr       */
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
		{
			if (!env_copy[i])
			{
				while (i--)
					free(env_copy[i]);
				return (free(env_copy), NULL);
			}
		}
		i++;
	}
	env_copy[i] = NULL;
	return (env_copy);
}

t_env	*create_env_node(char *env_var)
{
	t_env	*node;
	char	*equal_pos;

	node = ft_secure_malloc(sizeof(t_env));
	equal_pos = ft_strchr(env_var, '=');
	if (equal_pos)
	{
		node->key = ft_strndup(env_var, equal_pos - env_var);
		node->value = ft_strdup(equal_pos + 1);
	}
	else
	{
		node->key = ft_strdup(env_var);
		node->value = NULL;
	}
	node->next = NULL;
	return (node);
}

t_env	*init_env_list(char **envp)
{
	t_env	*head;
	t_env	*current;
	int		i;

	head = NULL;
	i = 0;

	while(envp[i])
	{
		t_env	*new_node;
		new_node = create_env_node(envp[i]);
		if (!new_node)
			return (NULL);
		if (!head)
			head = new_node;
		else
			current->next = new_node;
		current = new_node;
		i++;
	}
	return (head);
}

char	*get_env_value(t_env *env, const char *key)
{
	while (env)
	{
		if(ft_strncmp(env->key, key, ft_strlen(key)) == 0)
			return env->value;
		env = env->next;
	}
	return (NULL);
}

int	set_env_value(t_env **env, const char *key, const char *value)
{
	t_env	*current;
	t_env	*new_node;
	
	current = *env;
	while(current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key)) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return (current->value == NULL);
		}
		current = current->next;
	}
	new_node = ft_secure_malloc(sizeof(t_env));
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = *env;
	*env = new_node;
	return (0);
}
