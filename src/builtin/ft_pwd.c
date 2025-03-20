/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:33:12 by tboulogn          #+#    #+#             */
/*   Updated: 2025/03/20 13:09:13 by tboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(char **envp)
{
	char	*pwd;
	pwd = get_env_value(envp, "PWD");
	if (!pwd)
		return (1);
	printf("%s\n", pwd);
	return (0);	
}
