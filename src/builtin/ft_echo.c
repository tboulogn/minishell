/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:31:10 by tboulogn          #+#    #+#             */
/*   Updated: 2025/03/31 16:03:44 by tboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_var_key(const char *str, int *i)
{
	int	start;

	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

char	*extract_text(const char *str, int *i)
{
	int		start;
	char	*text;

	start = *i;
	while (str[*i] && str[*i] != '$')
		(*i)++;
	text = ft_substr(str, start, *i - start);
	return (text);
}

char	*expand_dollar(const char *str, int *i, t_env *env, int e_status)
{
	char	*key;
	char	*value;
	t_env	*node;

	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa((e_status)));
	}
	key = get_var_key(str, i);
	node = get_env_var(env, key);
	free(key);
	if (node && node->value)
		value = ft_strdup(node->value);
	else
		value = ft_strdup("");
	return (value);
}

char	*expand_vars(const char *str, t_env *env_list, int e_status)
{
	int		i;
	char	*res;
	char	*chunk;
	char	*tmp;

	i = 0;
	res = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			chunk = expand_dollar(str, &i, env_list, e_status);
		}
		else
			chunk = extract_text(str, &i);
		tmp = res;
		res = ft_strjoin(res, chunk);
		free(chunk);
		free(tmp);
	}
	return (res);
}

int	ft_echo(t_args *args, t_env *env_list)
{
	char	**argv;
	char	*expanded;
	int		i;
	int		n_flag;

	if (!args || !args->cmd || !args->cmd->cmd_tab)
		return (1);
	argv = args->cmd->cmd_tab;
	i = 0;
	n_flag = 0;
	while (argv[++i] && ft_strncmp(argv[i], "-n", 2) == 0)
		n_flag = 1;
	while (argv[i])
	{
		expanded = expand_vars(argv[i], env_list, args->e_status);
		ft_putstr_fd(expanded, 1);
		free(expanded);
		if (argv[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!n_flag)
		ft_putstr_fd("\n", 1);
	return (0);
}
