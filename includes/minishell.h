/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:41:05 by ryada             #+#    #+#             */
/*   Updated: 2025/03/19 14:30:16 by ryada            ###   ########.fr       */
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
# include "../libft_master/libft.h"

# define PROMPT "minishell:~$"

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
	struct s_token	*next;
}	t_token;


//char **arg isn't more like char **cmd? bc we store the table of cmds from args??
typedef struct s_cmd
{
	char			**args;
	char			*infile;
	char			*outfile;
	int				append;
	int				pipe;
	struct s_cmd	*next;
}	t_cmd;

/* ************************************************************************** */
/*                                   UTILS                                    */
/* ************************************************************************** */
void	*ft_secure_malloc(size_t bytes);
int		is_whitespace(char c);
int 	is_special_char(char c);
char	*ft_strndup(const char *s, size_t len);

/* ************************************************************************** */
/*                                    FREE                                    */
/* ************************************************************************** */
void	free_token(t_token *tokens);
void	free_cmd_list(t_cmd *cmd);

/* ************************************************************************** */
/*                                TOKENIZATION                                */
/* ************************************************************************** */
t_token	*tokenize(char *input);
void	add_token(t_token **tokens, char *value, t_token_type type);
char	*extract_word(char *input, int *i);
t_cmd	*parse_token(t_token *tokens);
t_cmd 	*create_new_cmd(void);
void	add_arg_to_cmd(t_cmd *cmd, char *arg);
void	print_cmd_list(t_cmd *cmd);


/* ************************************************************************** */
/*                                  EXEC                                      */
/* ************************************************************************** */
int		ft_check_buildin(t_cmd *cmd);
void	ft_exec(char **envp, t_cmd *c);


#endif