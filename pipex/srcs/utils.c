/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 08:33:43 by ryada             #+#    #+#             */
/*   Updated: 2025/03/12 11:53:42 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}

int	ft_open_file(char *filename, int second)
{
	int	fd;

	if (second)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("[Error] Cannot open file: ", 2);
		ft_putendl_fd(filename, 2);
		exit(1);
	}
	return (fd);
}

void	ft_error_handler(int type, char **cmd_tab, char *cmd_path)
{
	if (type == 1)
	{
		ft_putstr_fd("[Error] Command parsing failed!\n", 2);
		ft_free_tab(cmd_tab);
		exit(1);
	}
	else if (type == 2)
	{
		ft_putstr_fd("[Error] Command not found! : ", 2);
		ft_putendl_fd(cmd_tab[0], 2);
		ft_free_tab(cmd_tab);
		exit(127);
	}
	else if (type == 3)
	{
		ft_putstr_fd("[Error] Commnd execution failed!: ", 2);
		ft_putendl_fd(cmd_tab[0], 2);
		free(cmd_path);
		ft_free_tab(cmd_tab);
		exit(1);
	}
}
