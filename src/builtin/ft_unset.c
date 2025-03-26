/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:10:40 by tboulogn          #+#    #+#             */
/*   Updated: 2025/03/24 17:56:31 by tboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	unset_env_var(t_env **env, const char *key)
{
	t_env	*current;
	t_env	*previous;

	if (!is_valid_key(key))
		return (printf("minishell: unset: `%s': not a valid identifier\n", key),
			1);
	current = *env;
	previous = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (previous)
				previous->next = current->next;
			else
				*env = current->next;
			free_env_node(current);
			return (0);
		}
		previous = current;
		current = current->next;
	}
	return (0);
}

int	ft_unset(t_args *args, t_env **env)
{
	char **argv;
	int i;

	if (!args || !args->cmd || !args->cmd->cmd_tab)
		return (1);
	argv = args->cmd->cmd_tab;
	i = 1;
	{
		unset_env_var(env, argv[i]);
		i++;
	}
	return (0);
}