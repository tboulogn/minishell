/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:34:18 by ryada             #+#    #+#             */
/*   Updated: 2025/03/12 12:07:24 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_edata	edata;

	if (argc < 5)
		return (ft_error_exit("[Error] Incorrect argument number!\n"), 1);
	edata = ft_init_edata(argc, argv);
	if (edata.here_doc)
		ft_here_doc(argc, argv[2]);
	edata.pid = malloc(sizeof(pid_t) * edata.num_cmds);
	if (!edata.pid)
		return (free(edata.pid),
			ft_error_exit("[Error] Memory allocation failed!\n"), 1);
	ft_create_process(argv, envp, edata);
	ft_wait_children(&edata);
	if (edata.pid != 0)
		free (edata.pid);
	return (edata.status);
}
