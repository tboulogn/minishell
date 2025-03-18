/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:32:40 by ryada             #+#    #+#             */
/*   Updated: 2025/03/18 13:44:07 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include "../../libft_master/libft.h"

//getenv.c//
char	*ft_getenv(char *key, char **envp);
char	*ft_check_exec_path(char *dir, char *cmd);
char	*ft_get_path(char *cmd, char **envp);

//pipex.c//
void	ft_error_handler(int type, char **cmd_tab, char *cmd_path);
void	ft_exec(char *cmd, char **envp);
void	ft_first_child(char **argv, int *pipe_fd, char **envp);
void	ft_second_child(char **argv, int *pipe_fd, char **envp);

//utils.c//
void	ft_free_tab(char **tab);
int		ft_open_file(char *filename, int second);
void	ft_error_handler(int type, char **cmd_tab, char *cmd_path);

#endif
