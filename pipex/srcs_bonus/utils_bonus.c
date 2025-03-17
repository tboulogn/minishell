/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 08:33:43 by ryada             #+#    #+#             */
/*   Updated: 2025/03/12 13:12:49 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	ft_open_file(char *filename, int mode, pid_t *pid)
{
	int	fd;

	if (mode == 0)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (mode == 1)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("[Error] Cannot open file: ", 2);
		ft_putendl_fd(filename, 2);
		free(pid);
		exit(1);
	}
	return (fd);
}

int	ft_arg_count(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}
