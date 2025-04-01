/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:07:24 by tboulogn          #+#    #+#             */
/*   Updated: 2025/04/01 15:13:05 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*create_env_node(char *env_var)
{
	char	*equal_pos;
	t_env	*node;

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

//initialize and set the next/chain list
t_env	*init_env_list(char **envp)
{
	t_env	*head;
	t_env	*current;
	t_env	*new_node;
	int		i;

	head = NULL;
	i = 0;
	while (envp[i])
	{
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

//check exec.c (ft_getenv)
char	*get_env_value(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(key)) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

t_env	*get_env_var(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(key)) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	set_env_value(t_env **env, const char *key, const char *value)
{
	t_env	*current;
	t_env	*new_node;

	current = *env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			printf("[DEBUG] Adding variable: key='%s', value='%s'\n", key, value);
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
