/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 10:19:42 by tboulogn          #+#    #+#             */
/*   Updated: 2025/04/18 11:40:33 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	exit_status(int i)
{
	static int	status = 0;

	if (i >= 0)
		status = i;
	return (status);
}

void	set_exit_status(int status)
{
	exit_status(status);
}

int	get_exit_status(void)
{
	return (exit_status(-1));
}
