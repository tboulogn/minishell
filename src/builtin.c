/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:55:34 by tboulogn          #+#    #+#             */
/*   Updated: 2025/03/19 20:14:05 by tboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_env(char **envp)
{
	if (!envp || !*envp)
		return (1);
	while(*envp)
	{
		printf("%s\n", *envp);
		envp++;
	}
	return (0);
}

int	ft_pwd(t_env *env_list)
{
	char	*pwd;
	pwd = get_env_value(env_list, "PWD");
	if (!pwd)
		return (1);
	printf("%s\n", pwd);
	return (0);	
}

int	ft_echo(t_cmd *cmd)
{
	int	i;
	int	n_flag;

	if (!cmd || !cmd->args[1])
		return (ft_putstr_fd("\n", 1), 0);
	i = 1;
	n_flag = 0;

	while (cmd->args[i] && ft_strncmp(cmd->args[i], "-n", 2) == 0)	
	{
		n_flag = 1;
		i++;
	}
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], 1);
		if (cmd->args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!n_flag)
		ft_putstr_fd("\n", 1);
	return (0);
}

int ft_cd(t_env **env, const char *new_path)
{
	DIR	*dir;
	char *old_pwd;

	dir = opendir(new_path);
	if (!dir)
	{
		perror("cd");
		return (1);
	}
	closedir(dir);
	old_pwd = get_env_value(*env, "PWD");
	if (old_pwd)
		set_env_value(env, "OLDPWD", old_pwd);
	set_env_value(env, "PWD", new_path);
	return (0);
}
