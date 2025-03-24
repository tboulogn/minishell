/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:41:05 by ryada             #+#    #+#             */
/*   Updated: 2025/03/24 19:41:03 by tboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include "../libft_master/libft.h"

# define PROMPT "minishell:~$ "

typedef enum e_token_type
{
	WORD,//cmd or just a str or filename
	PIPE,// '|'
	REDIR_IN,// '<'
	REDIR_OUT,// '>'
	HEREDOC,// '<<'
	APPEND,// '>>'
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd t_cmd;

struct s_cmd
{
	char	**cmd_tab;
	char	*cmd_path;
	t_cmd	*prev;
	t_cmd	*next;
};

typedef struct s_args
{
	t_cmd			*cmd;
	int				cmd_count;
	char			*infile;
	char			*outfile;
	char			*append_outfile;
	char			*limiter;
	int				pipe;
	// struct s_args	*next;
}	t_args;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env 	*next;
}	t_env;

typedef struct s_pipe
{
	int		prev[2];
	int		next[2];
    pid_t	*pid;
}	t_pipe;

/* ************************************************************************** */
/*                                   UTILS                                    */
/* ************************************************************************** */
void	*ft_secure_malloc(size_t bytes);
int		is_whitespace(char c);
int 	is_special_char(char c);
char	*ft_strndup(const char *s, size_t len);
char	*ft_strjoin_three(char const *s1, char const *s2, const char *s3);

/* ************************************************************************** */
/*                                   UTILS_2                                  */
/* ************************************************************************** */
int		ft_strcmp(const char *s1, const char *s2);
void	ft_free_tab(char **tab);
char	*ft_strjoin_3(char *s1, char *s2, char *s3);
int		is_valid_key(const char *key);

/* ************************************************************************** */
/*                                    FREE                                    */
/* ************************************************************************** */
void	free_token(t_token *tokens);
void	free_cmd_list(t_args *cmd);
void	free_env_array(char **env_array);
void	free_env_node(t_env *node);

/* ************************************************************************** */
/*                                  PARSING                                   */
/* ************************************************************************** */

char	*extract_word(char *input, int *i);
void init_token(t_token *tokens);
t_token	*tokenize(char *input);
void	add_token(t_token **tokens, char *value, t_token_type type);
t_args	*parse_token(t_token *tokens);
t_args	*create_new_args(void);
void add_cmd(t_args *args, char *word);
t_cmd *create_cmd_from_list(t_list *words);
void	add_file(t_args *args, char *filename, int type);
void 	print_cmd_list(t_args *args);

/* ************************************************************************** */
/*                                  EXEC                                      */
/* ************************************************************************** */
int		ft_check_buildin(t_args *args);
void	ft_exec(t_args *args, t_env *env_list);

/* ************************************************************************** */
/*                                   BUILTIN                                  */
/* ************************************************************************** */
int		ft_env(t_env *env_list);
int		ft_pwd(t_env *env_list);
int		ft_echo(t_args *args);
int		ft_cd(t_env **env_list, char *path);
int		ft_export(t_args *args, t_env **env);
int		ft_unset(t_args *args, t_env **env);

/* ************************************************************************** */
/*                                ENVIRONNEMENT                               */
/* ************************************************************************** */
t_env	*create_env_node(char *env_var);
t_env	*init_env_list(char **envp);
char	*get_env_value(t_env *env, const char *key);
t_env	*get_env_var(t_env *env, char *key);
int		set_env_value(t_env **env, const char *key, const char *value);


/* ************************************************************************** */
/*                                   CHCKER                                   */
/* ************************************************************************** */
int		check_syntax_error(t_token *tokens);

/* ************************************************************************** */
/*                                     PIPE                                   */
/* ************************************************************************** */
void	pipex(t_args *args, t_env *env_list);

#endif