/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:42:02 by ryada             #+#    #+#             */
/*   Updated: 2025/04/15 16:12:19 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	built_in(t_args *args, t_env **env_list)
{
	char	*path;

	if (ft_strncmp(args->cmd->cmd_tab[0], "env", 3) == 0)
		ft_env(*env_list);
	else if (ft_strncmp(args->cmd->cmd_tab[0], "pwd", 3) == 0)
		ft_pwd(*env_list);
	else if (ft_strncmp(args->cmd->cmd_tab[0], "echo", 4) == 0)
		ft_echo(args, *env_list, 0);
	else if (ft_strncmp(args->cmd->cmd_tab[0], "cd", 2) == 0)
	{
		path = NULL;
		if (args->cmd->cmd_tab[1])
			path = args->cmd->cmd_tab[1];
		ft_cd(env_list, path);
	}
	else if (ft_strcmp(args->cmd->cmd_tab[0], "export") == 0)
		ft_export(args, env_list);
	else if (ft_strncmp(args->cmd->cmd_tab[0], "unset", 5) == 0)
		ft_unset(args, env_list);
	else if (ft_strcmp(args->cmd->cmd_tab[0], "exit") == 0)
		ft_exit(args, env_list);
}

char	**prepare_envp(t_args *args, t_env *env, t_pipe *pro, char **cmd_tab)
{
	char	**envp;

	if (!cmd_tab || !cmd_tab[0] || cmd_tab[0][0] == '\0')
		error_cmd_not_found(args, env, pro, NULL);
	envp = env_list_to_envp(env);
	if (!envp)
	{
		free_ereaser(args, env, pro);
		exit(1);
	}
	return (envp);
}

void	free_array_and_struct(t_args **args, t_env **env_list,
			t_pipe **pro, char ***envp_arr)
{
	if (*envp_arr)
	{
		free_env_array(*envp_arr);
		*envp_arr = NULL;
	}
	free_ereaser(*args, *env_list, *pro);
}

void	external(t_args *args, t_env *env_list, t_pipe *pro)
{
	char	*cmd_path;
	char	**cmd_tab;
	char	**envp_arr;
	int		err;

	cmd_tab = args->cmd->cmd_tab;
	envp_arr = prepare_envp(args, env_list, pro, cmd_tab);
	cmd_path = define_cmd_path(cmd_tab, env_list);
	if (!cmd_path)
		error_cmd_not_found(args, env_list, pro, envp_arr);
	err = check_cmd_path(cmd_path);
	if (err)
	{
		free_array_and_struct(&args, &env_list, &pro, &envp_arr);
		free(cmd_path);
		exit(err);
	}
	if (execve(cmd_path, cmd_tab, envp_arr) == -1)
	{
		free_array_and_struct(&args, &env_list, &pro, &envp_arr);
		free(cmd_path);
		perror("execve");
		exit(1);
	}
}

void	ft_exec(t_args *args, t_env **env_list, t_pipe *pro)
{
	if (!args || !args->cmd || !args->cmd->cmd_tab || !args->cmd->cmd_tab[0])
		return ;
	if (!ft_check_buildin(args))
		built_in(args, env_list);
	else
		external(args, *env_list, pro);
}
