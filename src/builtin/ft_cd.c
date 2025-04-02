/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:55:34 by tboulogn          #+#    #+#             */
/*   Updated: 2025/04/01 15:24:12 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    update_pwd_vars(t_env **env_list, char *old_dir)
{
    char    new_dir[4096];

    if (getcwd(new_dir, sizeof(new_dir)) == NULL)
        return ;
    set_env_value(env_list, "OLDPWD", old_dir);
    set_env_value(env_list, "PWD", new_dir);
}

int    ft_cd_to_oldpwd(t_env **env_list, char *current_dir)
{
    t_env    *oldpwd_var;

    oldpwd_var = get_env_var(*env_list, "OLDPWD");
    if (!oldpwd_var || !oldpwd_var->value)
        return (ft_putstr_fd("cd: OLDPWD not set\n", 2), 1);
    if (chdir(oldpwd_var->value) != 0)
        return (perror("cd"), 1);
    printf("%s\n", oldpwd_var->value);
    update_pwd_vars(env_list, current_dir);
    return (0);
}

int    ft_cd_to_parent(t_env **env_list, char *current_dir)
{
    if (chdir("..") != 0)
        return (perror("cd"), 1);
    update_pwd_vars(env_list, current_dir);
    return (0);
}

int    ft_cd(t_env **env_list, char *path)
{
    char    current_dir[4096];
    t_env    *home_var;
    t_env    *oldpwd_var;

    if (getcwd(current_dir, sizeof(current_dir)) == NULL)
        ft_strlcpy(current_dir,
            get_env_value(*env_list, "PWD"), sizeof(current_dir));
    if (!path || ft_strlen(path) == 0)
    {
        home_var = get_env_var(*env_list, "HOME");
        if (!home_var || !home_var->value)
            return (ft_putstr_fd("cd: HOME not set\n", 2), 1);
        path = home_var->value;
    }
    else if (ft_strcmp(path, "-") == 0)
        return (ft_cd_to_oldpwd(env_list, current_dir));
    else if (ft_strcmp(path, "..") == 0)
        return (ft_cd_to_parent(env_list, current_dir));
    else if (ft_strcmp(path, ".") == 0)
        return (update_pwd_vars(env_list, current_dir), 0);
    if (chdir(path) != 0)
        return (perror("cd"), 1);
    update_pwd_vars(env_list, current_dir);
    return (0);
}
