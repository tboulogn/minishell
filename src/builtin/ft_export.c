/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 18:33:38 by tboulogn          #+#    #+#             */
/*   Updated: 2025/03/21 19:34:12 by tboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_valid_key(const char *key)
{
	while (*key)
	{
		if(!(*key == '_' || is_capletter(*key)))
			return (0);
		key++;
	}
	return (1);
}

t_env	*sort_env(t_env *env_list)
{
	t_env	*current;
	t_env	*next_node;
	char	*temp_key;
	char	*temp_value;
	int		swapped;

	if (!env_list)
		return (NULL);
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		current = env_list;
		while (current->next)
		{
			next_node = current->next;
			if (ft_strcmp(current->key, next_node->key) > 0)
			{
				temp_key = current->key;
				temp_value = current->value;
				current->key = next_node->key;
				current->value = next_node->value;
				next_node->key = temp_key;
				next_node->value = temp_value;
				swapped = 1;
			}
			current = current->next;
		}
	}
	return (env_list);
}
