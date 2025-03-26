/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:42:02 by ryada             #+#    #+#             */
/*   Updated: 2025/03/26 14:14:35 by tboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_getenv_from_list(char *key, t_env *env_list)
{
	while (env_list)
	{
		if (ft_strncmp(env_list->key, key, ft_strlen(key) + 1) == 0)
			return (env_list->value);
		env_list = env_list->next;
	}
	return (NULL);
}

char	*ft_check_exec_path(char *dir, char *cmd)
{
	char	*path;
	char	*exec;

	path = ft_strjoin(dir, "/");
	if (!path)
		return (NULL);
	exec = ft_strjoin(path, cmd);
	free(path);
	if (!exec)
		return (NULL);
	if (!access(exec, F_OK) && !access(exec, X_OK))
		return (exec);
	free(exec);
	return (NULL);
}

char	*ft_get_path(char *cmd, t_env *env_list)
{
	int		i;
	char	*exec;
	char	*env_path;
	char	**all_paths;

	env_path = ft_getenv_from_list("PATH", env_list);
	if (!env_path)
		return (NULL);
	all_paths = ft_split(env_path, ':');
	if (!all_paths)
		return (NULL);
	i = 0;
	exec = NULL;
	while (all_paths[i] && !exec)
	{
		exec = ft_check_exec_path(all_paths[i], cmd);
		i++;
	}
	ft_free_tab(all_paths); // free the split array
	return (exec);
}

int ft_check_buildin(t_args *args)
{
	char *name;

	if (!args || !args->cmd)
		return (1);
	name = args->cmd->cmd_tab[0];
	if (!name)
		return (1);
	if (ft_strncmp(name, "echo", 5) == 0
		|| ft_strncmp(name, "cd", 3) == 0
		|| ft_strncmp(name, "pwd", 4) == 0
		|| ft_strncmp(name, "export", 7) == 0
		|| ft_strncmp(name, "unset", 6) == 0
		|| ft_strncmp(name, "env", 4) == 0
		|| ft_strncmp(name, "exit", 5) == 0)
		return (0);
	return (1);
}

//Bc we need an array of array for execve
char	**env_list_to_envp(t_env *env)
{
	int		count;
	t_env	*temp;
	char	**envp;
	int		i;

	count = 0;
	i = 0;
	temp = env;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	while (env)
	{
		envp[i] = ft_strjoin_3(env->key, "=", env->value); // custom join function
		i++;
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

void	built_in(t_args *args, t_env **env_list)
{
	printf("BUILT_IN CMD\n");//modify this
	printf("================\n");
	if (ft_strncmp(args->cmd->cmd_tab[0], "env", 3) == 0)
		ft_env(*env_list);
	else if (ft_strncmp(args->cmd->cmd_tab[0], "pwd", 3) == 0)
		ft_pwd(*env_list);
	else if (ft_strncmp(args->cmd->cmd_tab[0], "echo", 4) == 0)
		ft_echo(args, *env_list);
	else if (ft_strncmp(args->cmd->cmd_tab[0], "cd", 2) == 0)
	{
		char *path;
		path = NULL;
		if (args->cmd->cmd_tab[1])
			path = args->cmd->cmd_tab[1]; 
		ft_cd(env_list, path);
	}
	else if (ft_strncmp(args->cmd->cmd_tab[0], "export", 6) == 0)	
		ft_export(args, env_list);
	else if (ft_strncmp(args->cmd->cmd_tab[0], "unset", 5) == 0)
		ft_unset(args, env_list);
	
	
}

void external(t_args *args, t_env *env_list)
{
	char	*cmd_path;
	char	**cmd_tab;
	char	**envp_arr;

	cmd_tab = args->cmd->cmd_tab;
	if (!cmd_tab || !cmd_tab[0])
	{
		printf("command not found\n");
		exit(127);
	}
	envp_arr = env_list_to_envp(env_list);
	if (ft_strchr(cmd_tab[0], '/'))
		cmd_path = ft_strdup(cmd_tab[0]);
	else
		cmd_path = ft_get_path(cmd_tab[0], env_list);
	if (!cmd_path)
	{
		printf("%s: command not found\n", cmd_tab[0]);
		exit(127);
	}
	execve(cmd_path, cmd_tab, envp_arr);
}

//without any frees
void	ft_exec(t_args *args, t_env **env_list)
{
	if (!args || !args->cmd || !args->cmd->cmd_tab || !args->cmd->cmd_tab[0])
		return ;
    if(!ft_check_buildin(args))
        built_in(args, env_list);
    else
		external(args, *env_list);
}
