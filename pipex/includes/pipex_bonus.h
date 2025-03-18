/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:32:40 by ryada             #+#    #+#             */
/*   Updated: 2025/03/18 13:43:52 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include "../../libft_master/libft.h"

//execution data structure
typedef struct s_edata
{
	int		here_doc;
	int		num_cmds;
	char	*current_cmd;
	pid_t	*pid;
	int		status;
	int		prev_pipe[2];
	int		next_pipe[2];
}	t_edata;

//child_bonus.c//
void	ft_first_child(char **argv, char **envp, t_edata edata);
void	ft_middle_child(char **envp, t_edata edata);
void	ft_last_child(char **argv, char **envp, t_edata edata);

//edata_bonus.c//
t_edata	ft_init_edata(int argc, char **argv);
void	ft_close_pipe(int *prev);
void	ft_update_pipe(int *prev, int *next);

//error_bonus.c//
void	ft_error_exit(char *msg);
void	ft_safe_print_error(const char *msg, const char *arg);
void	ft_cmd_error_handler(int type, char **cmd_tab,
			char *cmd_path, pid_t *pid);
void	ft_general_error_handler(t_edata edata, int type);

//exec_bonus.c//
void	ft_exec(char *cmd, char **envp, pid_t *pid);

//getenv_bonus.c//
char	*ft_getenv(char *key, char **envp);
char	*ft_check_exec_path(char *dir, char *cmd);
char	*ft_get_path(char *cmd, char **envp);

//heredoc_bonus.c//
void	ft_handle_here_doc_child(int *pipe_fd, char *limiter);
void	ft_here_doc(int argc, char *limiter);

//process_bonus.c//
void	ft_child_process(char **argv, char **envp, t_edata edata, int i);
void	ft_create_process(char **argv, char **envp, t_edata edata);
void	ft_wait_children(t_edata *edata);

//utils_bonus.c//
void	ft_free_tab(char **tab);
int		ft_open_file(char *filename, int mode, pid_t *pid);
int		ft_arg_count(char **argv);

#endif