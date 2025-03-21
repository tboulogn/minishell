/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:42:02 by ryada             #+#    #+#             */
/*   Updated: 2025/03/21 17:21:05 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_getenv(char *key, char **envp)
{
	int		i;
	size_t	len;

	len = ft_strlen(key);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, len) == 0 && envp[i][len] == '=')
			return (envp[i] + (len + 1));
		i++;
	}
	return (NULL);
}

char	*ft_check_exec_path(char *dir, char *cmd)
{
	char	*path;
	char	*exec;

	path = ft_strjoin(dir, "/");
	exec = ft_strjoin(path, cmd);
	free(path);
	if (!access(exec, F_OK) && !access(exec, X_OK))
		return (exec);
	free(exec);
	return (NULL);
}

char	*ft_get_path(char *cmd, char **envp)
{
	int		i;
	char	*exec;
	char	*env_path;
	char	**all_paths;

	env_path = ft_getenv("PATH", envp);
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
		if (!exec)
			free(exec);
		i++;
	}
	// ft_free_tab(all_paths);
	return (exec);
}


int ft_check_buildin(t_args *args)
{
    int i;

    i = 0;
    while(args->cmds[i])
    {
        if (ft_strncmp(args->cmds[i], "echo", ft_strlen(args->cmds[i])) == 0
            || ft_strncmp(args->cmds[i], "cd" , ft_strlen(args->cmds[i])) == 0
            || ft_strncmp(args->cmds[i], "pwd", ft_strlen(args->cmds[i])) == 0
            || ft_strncmp(args->cmds[i], "export", ft_strlen(args->cmds[i])) == 0
            || ft_strncmp(args->cmds[i], "unset", ft_strlen(args->cmds[i])) == 0
            || ft_strncmp(args->cmds[i], "env", ft_strlen(args->cmds[i])) == 0
            || ft_strncmp(args->cmds[i], "exit", ft_strlen(args->cmds[i])) == 0)
            return (0);
        i++;
    }
    return (1);
}

// void	ft_exec(char **envp, t_cmd *c)
// {
// 	char	**cmd_tab;
// 	char	*cmd_path;

//     if(!ft_check_buildin(c))
//     {
//         printf("BUILT_IN CMD\n");//modify this
//     //     call the built-in functions here!
//     }
//     else
//         printf("EXTERNAL CMD\n");//modify this
//     printf("================\n");
//     cmd_tab = args->cmds;
// 	// cmd_tab = ft_split(cmd, ' ');
// 	// if (!cmd_tab || !cmd_tab[0])
// 	// 	ft_cmd_error_handler(1, cmd_tab, NULL, pid);
// 	if (ft_strchr(cmd_tab[0], '/'))
// 		cmd_path = ft_strdup(cmd_tab[0]);
// 	else
// 		cmd_path = ft_get_path(cmd_tab[0], envp);
// 	// if (!cmd_path)
// 	// 	ft_cmd_error_handler(2, cmd_tab, cmd_path, pid);
// 	// if (execve(cmd_path, cmd_tab, envp) == -1)
// 	// 	ft_cmd_error_handler(3, cmd_tab, cmd_path, pid);
//     if (execve(cmd_path, cmd_tab, envp) == -1)
//         printf("CMD NOT FOUND\n");
// 	// free(cmd_path);
// 	// ft_free_tab(cmd_tab);
// }



//without any frees
void	ft_exec(char **envp, t_args *args)
{
	char	**cmd_tab;
	char	*cmd_path;

    if(!ft_check_buildin(args))
    {
        printf("BUILT_IN CMD\n");//modify this
        printf("================\n");
        if (ft_strncmp(args->cmds[0], "env", ft_strlen(args->cmds[0])) == 0)
            ft_env(envp);
        else if (ft_strncmp(args->cmds[0], "pwd", ft_strlen(args->cmds[0])) == 0)
            ft_pwd(envp);
		// else if (ft_strncmp(args->cmds[0], "echo", ft_strlen(args->cmds[0])) == 0)
		// 	ft_echo(args);
		// else if (ft_strncmp(args->cmds[0], "cd", ft_strlen(args->cmds[0])) == 0)
		// {
		// 	if (!args->cmds[1])
		// 		ft_cd(envp, get_env_value(envp, "HOME"));
		// 	else
		// 		ft_cd(envp, args->cmds[1]);
		// }
    }
    else
    {
        printf("EXTERNAL CMD\n");//modify this
        printf("============\n");
        cmd_tab = args->cmds;
        if (ft_strchr(cmd_tab[0], '/'))
            cmd_path = ft_strdup(cmd_tab[0]);
        else
            cmd_path = ft_get_path(cmd_tab[0], envp);
        if (execve(cmd_path, cmd_tab, envp) == -1)
            printf("%s: command not found\n", cmd_tab[0]);
    }
}
