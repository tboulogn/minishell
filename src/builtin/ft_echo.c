/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:31:10 by tboulogn          #+#    #+#             */
/*   Updated: 2025/03/25 12:35:11 by tboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	char	quote;
	char	*res;

	res = ft_secure_malloc((ft_strlen(str) + 1) * sizeof(char));
	i = 0;
	j = 0;
	quote = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && !quote)
			quote = str[i];
		else if (str[i] == quote)
			quote = 0;
		else
			res[j++] = str[i];
		i++;
	}
	res[j] = '\0';
	return (res);
}

int	ft_echo(t_args *args)
{
	char	**argv;
	char	*clean;
	int		i;
	int		n_flag;

	if (!args || !args->cmd || !args->cmd->cmd_tab)
		return (1);
	argv = args->cmd->cmd_tab;
	i = 1;
	n_flag = 0;
	while (argv[i] && ft_strncmp(argv[i], "-n", 2) == 0)
	{
		n_flag = 1;
		i++;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		if (argv[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!n_flag)
		ft_putstr_fd("\n", 1);
	return (0);
}

