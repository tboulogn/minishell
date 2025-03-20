/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:32:35 by tboulogn          #+#    #+#             */
/*   Updated: 2025/03/20 09:54:05 by tboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
