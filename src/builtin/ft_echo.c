/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:31:10 by tboulogn          #+#    #+#             */
/*   Updated: 2025/04/18 10:39:32 by tboulogn         ###   ########.fr       */
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

char	*expand_dollar(const char *str, int *i, t_env *env, int j)
{
	char	*key;
	char	*value;
	char	*status;
	t_env	*node;

	if (str[*i] == '?')
	{
		(*i)++;
		status = ft_itoa(get_exit_status());
		if (!status || status[0] == '\0')
			return (ft_strdup("0"));
		while (status[++j])
		{
			if (!ft_isdigit(status[j]))
				return (free(status), ft_strdup("0"));
		}
		return (status);
	}
	key = get_var_key(str, i);
	node = get_env_var(env, key);
	if (node && node->value)
		value = ft_strdup(node->value);
	else
		value = ft_strdup("");
	return (free(key), value);
}

int	check_n_flag(char *str)
{
	int	i;

	if (!str || str[0] != '-' || str[1] != 'n')
		return (0);
	i = 2;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(t_args *args, t_env *env_list, int i)
{
	char	**argv;
	char	*expanded;
	int		n_flag;

	if (!args || !args->cmd || !args->cmd->cmd_tab)
		return (1);
	argv = args->cmd->cmd_tab;
	n_flag = 0;
	while (argv[++i] && check_n_flag(argv[i]))
		n_flag = 1;
	while (argv[i])
	{
		if (args->cmd->sq[i])
			expanded = ft_strdup(argv[i]);
		else
			expanded = expand_vars(argv[i], env_list, 0);
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
