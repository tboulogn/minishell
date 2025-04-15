/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:41:05 by ryada             #+#    #+#             */
/*   Updated: 2025/04/15 17:47:49 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <string.h>
# include <wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include "../libft_master/libft.h"

# define PROMPT "minishell:~"

extern volatile	sig_atomic_t	g_signal;

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND,
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char			**cmd_tab;
	char			*cmd_path;
	bool			*sq;
	bool			*dq;
	int				here_doc_fd;
	char			*infile;
	char			*outfile;
	char			*append_outfile;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_args
{
	t_cmd			*cmd;
	int				cmd_count;
	char			**limiter;
	int				here_doc_count;
	int				pipe;
	int				index;
}	t_args;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_pipe
{
	int				prev[2];
	int				next[2];
	pid_t			*pid;
}	t_pipe;

/* ************************************************************************** */
/*                                   BUILTIN                                  */
/* ************************************************************************** */
//ft_cd.c//
void		update_pwd_vars(t_env **env_list, char *old_dir);
int			ft_cd_to_oldpwd(t_env **env_list, char *current_dir);
int			ft_cd_to_parent(t_env **env_list, char *current_dir);
int			ft_cd(t_env **env_list, char *path);
//ft_echo.c//
char		*get_var_key(const char *str, int *i);
char		*extract_text(const char *str, int *i);
char		*expand_dollar(const char *str, int *i, t_env *env, int j);
int			check_n_flag(char *str);
int			ft_echo(t_args *args, t_env *env_list, int i);
//ft_env.c//
int			ft_env(t_env *env_list);
//ft_exit.c//
int			ft_exit(t_args *args, t_env **env);
//ft_export.c//
char		**env_to_array(t_env *env);
void		sort_env_array(char **env_array);
void		print_sorted_env(t_env *env);
int			export_with_equal(char *arg, t_env **env);
int			ft_export(t_args *args, t_env **env);
//ft_pwd.c//
int			ft_pwd(t_env *env_list);
//ft_unset.c//
int			unset_env_var(t_env **env, const char *key);
int			ft_unset(t_args *args, t_env **env);

/* ************************************************************************** */
/*                                   ENV                                      */
/* ************************************************************************** */
t_env		*create_env_node(char *env_var);
t_env		*init_env_list(char **envp);
char		*get_env_value(t_env *env, const char *key);
t_env		*get_env_var(t_env *env, char *key);
int			set_env_value(t_env **env, const char *key, const char *value);

/* ************************************************************************** */
/*                                  EXEC                                      */
/* ************************************************************************** */
//exec_error.c//
int			check_cmd_path(char *path);
void		error_cmd_not_found(t_args *args, t_env *env_list, t_pipe *pro, char **envp_arr);
//exec_helper.c//
int			ft_check_buildin(t_args *args);
int			count_env_line(t_env *env);
//exec_path.c//
char		*ft_getenv_from_list(char *key, t_env *env_list);
char		*ft_check_exec_path(char *dir, char *cmd);
char		*ft_get_path(char *cmd, t_env *env_list);
char		**env_list_to_envp(t_env *env);
char		*define_cmd_path(char **cmd_tab, t_env *env);
//exec.c//
void		built_in(t_args *args, t_env **env_list);
char		**prepare_envp(t_args *args, t_env *env, t_pipe *pro, char **cmd_tab);
void		free_array_and_struct(t_args **args, t_env **env_list, t_pipe **pro, char ***envp_arr);
void		external(t_args *args, t_env *env_list, t_pipe *pro);
void		ft_exec(t_args *args, t_env **env_list, t_pipe *pro);

/* ************************************************************************** */
/*                                    FREE                                    */
/* ************************************************************************** */
void		free_token(t_token *tokens);
void		free_cmd_list(t_args *cmd);
void		free_env_array(char **env_array);
void		free_env_node(t_env *node);
void		free_env_list(t_env *env);
void		ft_free_cmd(t_cmd *cmd);
void		free_ereaser(t_args *args, t_env *env, t_pipe *pro);

/* ************************************************************************** */
/*                                  PARSING                                   */
/* ************************************************************************** */
//parsing_quotes_1.c//
void		handel_quoates(bool *open, bool *has_content, bool *has, bool other_quote_open);
void		update_content(bool *s_open, bool *d_open, bool *s_content, bool *d_content);
char		*clean_word_quotes(const char *str);
void		update_open_bool(bool *s_open, bool	*d_open, bool *s_content, bool *d_content);
void		quotes_update(const char *str, bool *has_sq, bool *has_dq);
//parsing_quotes_2.c//
bool		is_inside_sigle_quote(const char *str, int dollar_index);
char		*update_quotes_and_clean(char *content, bool *sq, bool *dq);
char		*expand_if_needed(char *cleaned, t_env *env_list);
//parsing_redir_pipe.c//
int			parsing_type(t_token *tokens);
void		first_limitter(char ***arr, char *line);
int			parse_pipe(t_args *args, t_cmd **current_cmd, t_env *env_list, t_list **word_list);
int			parse_redir(t_args *args, t_cmd **current_cmd, t_env *env_list, t_list **word_list);
void		parse_here_doc(t_token *tokens, t_args *args);
//parsing_chcker.c//
bool		quotes_closed_str(const char *str, bool *has_sq, bool *has_dq);
void		syntax_error_message(int type);
int			syntax_error_code(t_token	*current);
int			check_syntax_error(t_token *tokens);
//parsing_helper_1.c//
char		*extract_word(char *input, int *i);
int			define_tokens(t_token **tokens, char *str, int i);
int			count_char(const char *str, char c);
char		*ft_strdup_exept(const char *s, char c);
//parsing_helper_2.c//
int			find_char_pos(char *str, char c);
void		add_file(t_cmd *cmd, char *str, t_token_type type);
//parsing1.c//
t_token		*tokenize(char *input);
void		add_token(t_token **tokens, char *value, t_token_type type);
t_args		*create_new_args(void);
void		add_cmd_back(t_args *args, t_cmd *new_cmd);
//parsing2.c//
t_cmd		*create_cmd_from_list(t_list *words, t_env *env_list);
void		parse_last_cmd(t_list **word_list, t_cmd **current_cmd, t_args *args, t_env *env_list);
t_args		*parse_token(t_token *tokens, t_env *env);
void		print_cmd_list(t_args *args);//delete this for the correction

/* ************************************************************************** */
/*                                     PIPE                                   */
/* ************************************************************************** */
//pipe_helper_1.c//
void		init_pipe_struct(t_pipe *pro, int cmd_count);
void	close_parent_pipes(t_pipe *pro);
void		close_child_pipes(t_pipe *pro);
void		update_pipe(int *prev, int *next);
//pipe_helper_2.c//
void		read_files(t_cmd *cmd, int fd, int type);
int			no_files(t_cmd *cmd);
void		init_temp_args(t_args *temp, t_cmd *current, int cmd_count, int i);
void		close_and_update(t_pipe *pro);
//pipe_here_doc.c//
void		set_here_doc_in(t_args *args, t_cmd *current);
int			prepare_here_doc(t_args *args, t_cmd *current);
void		ft_handle_here_doc_child(int *pipe_fd, char *limiter);
int			ft_here_doc(char *limiter);
//pipe_process.c//
void		single_child(t_args *args, t_cmd *cmd, t_env *env_list, t_pipe pro);
void		first_child(t_args *args, t_cmd *cmd, t_env *env_list, t_pipe pro);
void		middle_child(t_args *args, t_cmd *cmd, t_env *env_list, t_pipe pro);
void		last_child(t_args *args, t_cmd *cmd, t_env *env_list, t_pipe pro);
void		child_process(t_args *temp, t_cmd *cmd, t_env *env_list, t_pipe pro);
//pipe.c//
void		wait_children(t_args *args, t_pipe *pro);
void		handle_pipe_and_fork(t_pipe	*pro, t_cmd *current, int i);
void		process_loop(t_args *args, t_env *env_list, t_pipe *pro, t_cmd	*current);
void		pipex(t_args *args, t_env **env_list);

/* ************************************************************************** */
/*                                  SIGNALS                                   */
/* ************************************************************************** */
void		init_signals(void);
void		sigint_handler(int sig);
void		sigquit_handler(int sig);
void		set_signal_child(void);

/* ************************************************************************** */
/*                                   UTILS                                    */
/* ************************************************************************** */
//utils.c//
void		*ft_secure_malloc(size_t bytes);
int			is_whitespace(char c);
int			is_special_char(char c);
char		*ft_strndup(const char *s, size_t len);
int			nb_len(int nb);
//utils_2.c//
int			ft_strcmp(const char *s1, const char *s2);
void		ft_free_tab(char **tab);
char		*ft_strjoin_3(char *s1, char *s2, char *s3);
int			is_valid_key(const char *key);
char		*ft_itoa(int nb);
//utils_3.c//
int			redirect_and_close(int old_fd, int new_fd);
int			is_number(const char *str);
long long	ft_atoll(const char *str);
char 		*ft_strjoin_and_free(char *s1, const char *s2, int free_s1);

#endif