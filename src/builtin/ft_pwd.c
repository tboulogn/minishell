/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:33:12 by tboulogn          #+#    #+#             */
/*   Updated: 2025/03/31 16:05:59 by tboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(t_env *env_list)
{
	char	*pwd;

	pwd = get_env_value(env_list, "PWD");
	if (!pwd)
		return (1);
	printf("%s\n", pwd);
	return (0);
}
