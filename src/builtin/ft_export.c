/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 18:33:38 by tboulogn          #+#    #+#             */
/*   Updated: 2025/04/16 15:55:21 by tboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**env_to_array(t_env *env)
{
	int		size;
	t_env	*tmp;
	char	**env_array;
	int		i;

	size = 0;
	tmp = env;
	i = 0;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	env_array = ft_secure_malloc(sizeof(char *) * (size + 1));
	tmp = env;
	while (tmp)
	{
		env_array[i++] = ft_strdup(tmp->key);
		tmp = tmp->next;
	}
	env_array[i] = NULL;
	return (env_array);
}

void	sort_env_array(char **env_array)
{
	int		i;
	int		size;
	char	*tmp;

	size = 0;
	while (env_array[size])
		size++;
	i = 0;
	while (i < size - 1)
	{
		if (ft_strcmp(env_array[i], env_array[i + 1]) > 0)
		{
			tmp = env_array[i];
			env_array[i] = env_array[i + 1];
			env_array[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
}

void	print_sorted_env(t_env *env)
{
	char	**env_array;
	int		i;
	t_env	*tmp;

	env_array = env_to_array(env);
	sort_env_array(env_array);
	i = 0;
	while (env_array[i])
	{
		tmp = env;
		while (tmp)
		{
			if (ft_strcmp(tmp->key, env_array[i]) == 0)
			{
				if (tmp->value)
					printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
				else
					printf("declare -x %s\n", tmp->key);
				break ;
			}
			tmp = tmp->next;
		}
		i++;
	}
	free_env_array(env_array);
}

int	export_with_equal(char *arg, t_env **env)
{
	char	*equal_pos;
	char	*key;
	char	*value;

	equal_pos = ft_strchr(arg, '=');
	key = ft_strndup(arg, equal_pos - arg);
	value = ft_strdup(equal_pos + 1);
	if (!is_valid_key(key))
	{
		printf("minishell: export: `%s': not a valid identifier\n", key);
		free(key);
		free(value);
		return (1);
	}
	set_env_value(env, key, value);
	free(key);
	free(value);
	return (0);
}

int	ft_export(t_args *args, t_env **env)
{
	int		i;
	char	**argv;
	t_env	*new;
	t_env	*var;

	argv = args->cmd->cmd_tab;
	if (!argv[1])
		return (print_sorted_env(*env), 1);
	i = 0;
	while (argv[++i])
	{
		if (ft_strchr(argv[i], '='))
			export_with_equal(argv[i], env);
		else
		{
			var = get_env_var(*env, argv[i]);
			if (!var)
			{
				new = create_env_node(argv[i]);
				new->next = *env;
				*env = new;
			}
		}
	}
	return (0);
}
