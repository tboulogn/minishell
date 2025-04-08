/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:39:55 by tboulogn          #+#    #+#             */
/*   Updated: 2025/04/08 16:05:15 by tboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*extract_word(char *input, int *i)
{
	int		start;
	char	quote;

	while (input[*i] && is_whitespace(input[*i]))
		(*i)++;
	start = *i;
	quote = 0;
	while (input[*i] && (quote || (!is_whitespace(input[*i])
				&& !is_special_char(input[*i]))))
	{
		if (input[*i] == '"' || input[*i] == '\'')
		{
			if (quote == 0)
				quote = input[*i];
			else if (quote == input[*i])
				quote = 0;
		}
		if (is_special_char(input[*i]) && !quote)
			break ;
		(*i)++;
	}
	return (ft_strndup(input + start, *i - start));
}

//init token, set up the next and prev(cahin-list)
void	add_token(t_token **tokens, char *value, t_token_type type)
{
	t_token	*new;
	t_token	*tmp;

	new = ft_secure_malloc(sizeof(t_token));
	if (!new)
		return ;
	new->value = ft_strdup(value);//call strdup for malloc
	new->type = type;
	new->next = NULL;
	new->prev = NULL;
	if (!*tokens)//if it is the new token
		*tokens = new;//set it as the start of the chain list
	else
	{
		tmp = *tokens;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;//add the new one as the next one of the last node
		new->prev = tmp;//the last node will be the prev of the new node
	}
}

int	define_tokens(t_token *tokens, char *str, int i)
{
	if (str[i] == '|')
		return(add_token(&tokens, "|", PIPE), 1);
	else if (str[i] == '>')
	{
		if (str[i + 1] == '>')
			return (add_token(&tokens, ">>", APPEND), 2);
		else
			return (add_token(&tokens, ">", REDIR_OUT), 1);
	}
	else if (str[i] == '<')
	{
		if (str[i + 1] == '<')
			return (add_token(&tokens, "<<", HEREDOC), 2);
		else
			return (add_token(&tokens, "<", REDIR_IN), 1);
	}
	return (0);
}

t_token	*tokenize(char *input)
{
	t_token	*tokens;
	int		i;
	char	*word;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		while (input[i] && is_whitespace(input[i]))
			i++;
		i += define_tokens(tokens, input, i);
		if (input[i])
		{
			word = extract_word(input, &i);
			add_token(&tokens, word, WORD);
			free(word);
		}
	}
		return (tokens);
}



//Initialize the argument infos we pass
t_args	*create_new_args(void)
{
	t_args	*new_args;

	new_args = ft_secure_malloc(sizeof(t_args));
	new_args->cmd_count = 0;
	new_args->limiter = NULL;
	new_args->here_doc_count = 0;
	new_args->pipe = 0;
	new_args->cmd = NULL;
	return (new_args);
}

//to init t_cmd and set prev/next of t_cmd
void	add_cmd_back(t_args *args, t_cmd *new_cmd)
{
	t_cmd	*last;

	if (!args || !new_cmd)
		return ;
	new_cmd->next = NULL;
	new_cmd->prev = NULL;
	new_cmd->here_doc_fd = -1;
	new_cmd->infile = NULL;
	new_cmd->outfile = NULL;
	new_cmd->append_outfile = NULL;
	if (!args->cmd)
	{
		args->cmd = new_cmd;
		return ;
	}
	last = args->cmd;
	while (last->next)
		last = last->next;
	last->next = new_cmd;
	new_cmd->prev = last;
}

int	count_char(const char *str, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while(str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

char	*ft_strdup_exept(const char *s, char c)
{
	size_t	len;
	char	*new_str;
	int		c_count;
	int		i;
	int		j;

	i = 0;
	c_count = count_char(s, c);
	len = ft_strlen(s) - c_count;
	new_str = malloc(len + 1 * sizeof(char));
	if (!new_str)
		return (NULL);
	j = 0;
	while(s[i])
	{
		if (s[i] != c)
		{
			new_str[j] = s[i];
			j++;
		}
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

void	handel_quoates(bool *open, bool *has_content, bool *has, bool other_quote_open)
{
	if (!other_quote_open)
	{
		if (*open && *has_content)
			*has = true;
		*open = !*open;
		if (!*open)
			*has_content = false;
	}
}

void	update_content(bool *s_open, bool *d_open, bool *s_content, bool *d_content)
{
	if (s_open)
		*s_content = true;
	if (d_open)
		*d_content = true;
}

bool	quotes_closed_str(const char *str, bool *has_sq, bool *has_dq)
{
	bool	s_open;
	bool	d_open;
	bool	s_content;
	bool	d_content;
	int		i;

	s_open = false;
	d_open = false;
	s_content = false;
	d_content = false;
	*has_sq = false;
	*has_dq = false;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !d_open)
			handel_quoates(&s_open, &s_content, has_sq, d_open);
		else if (str[i] == '"' && !s_open)
			handel_quoates(&d_open, &d_content, has_dq, s_open);
		update_content(&s_open, &d_open, &s_content, &d_content);
		i++;
	}
	return (!s_open && !d_open);
}

char *clean_word_quotes(const char *str)
{
	size_t len;
	char *tmp;
	char *cleaned;
	char *final;

	len = ft_strlen(str);
	if ((ft_strcmp(str, "''") == 0) || (ft_strcmp(str, "\"\"") == 0))
		return (ft_strdup(""));
	if (str[0] == '\'' && str[len - 1] == '\'' && len >= 2)
		return (ft_strdup_exept(str, '\''));
	else if (str[0] == '"' && str[len - 1] == '"' && len >= 2)
		return (ft_strdup_exept(str, '"'));
	if (ft_strnstr(str, "''", len) || ft_strnstr(str, "\"\"", len))
	{
		tmp = ft_strdup(str);
		cleaned = ft_strdup_exept(tmp, '\'');
		final = ft_strdup_exept(cleaned, '"');
		free(tmp);
		free(cleaned);
		return final;
	}
	return (ft_strdup(str));
}

t_cmd	*create_cmd_from_list(t_list *words, t_env *env_list)
{
	t_cmd	*cmd;
	int		i;
	t_list	*next;
	char	*cleaned;
	char	*expanded;

	cmd = ft_secure_malloc(sizeof(t_cmd));
	i = ft_lstsize(words);
	cmd->cmd_tab = ft_secure_malloc(sizeof(char *) * (i + 1));
	cmd->sq = ft_calloc(i, sizeof(bool));
	cmd->dq = ft_calloc(i, sizeof(bool));
	i = 0;
	while (words)
	{
		if (!quotes_closed_str(words->content, &cmd->sq[i], &cmd->dq[i]))
		{
			ft_putstr_fd("Syntax error: unclosed quote\n", 2); 
			ft_free_cmd(cmd);
			return (NULL);
		}
		cleaned = clean_word_quotes(words->content);
		if (!cmd->dq[i])
		{
			expanded = expand_vars(cleaned, env_list);
			free(cleaned);
			cleaned = expanded;
		}
		cmd->cmd_tab[i++] = cleaned;
		next = words->next;
		free(words->content);
		free(words);
		words = next;
	}
	cmd->cmd_tab[i] = NULL;
	return (cmd);
}

void	add_file(t_cmd *cmd, char *str, t_token_type type)
{
	if (!cmd || !str)
		return;
	if (type == REDIR_IN)
		cmd->infile = ft_strdup(str);
	else if (type == REDIR_OUT)
		cmd->outfile = ft_strdup(str);
	else if (type == APPEND)
		cmd->append_outfile = ft_strdup(str);
}

char	**add_malloc_line(char **tab, char *str, int i)
{
	char	**new_tab;
	int		j;

	new_tab = malloc(sizeof(char *) * (i + 1));
	if (!new_tab)
		return (NULL);
	j = 0;
	if (i == 0)
		new_tab[j] = ft_strdup(str);
	else
	{
		while (j < i)
		{
			new_tab[j] = ft_strdup(tab[j]);
			free(tab[j]);
			j++;
		}
		new_tab[j] = ft_strdup(str);
		free(tab);
	}
	new_tab[j + 1] = NULL;
	return (new_tab);
}


t_args *parse_token(t_token *tokens, t_env *env_list)//store the argument info into t_args by using t_token
{
	t_args *args;
	t_cmd *current_cmd;
	t_list *word_list;//linked chain (char *) of cmds
	t_cmd *final_cmd;
	int i;

	args = create_new_args();//initialize t_args
	current_cmd = NULL;
	word_list = NULL;
	i = 0;
	while (tokens)
	{
		// If it's a pipe, finalize the current command and reset
		if (tokens->type == PIPE)
		{
			if (word_list)
			{
				current_cmd = create_cmd_from_list(word_list, env_list);
				if (!current_cmd)
					return (free_cmd_list(args), NULL);
				add_cmd_back(args, current_cmd);
				args->cmd_count++;
				word_list = NULL;
			}
			args->pipe++;
			tokens = tokens->next;
			current_cmd = NULL;
			continue;
		}
		// Handle heredoc (collect limiter string)
		if (tokens->type == HEREDOC && tokens->next && tokens->next->type == WORD)
		{
			args->here_doc_count++;
			args->limiter = add_malloc_line(args->limiter, tokens->next->value, i++);
			tokens = tokens->next;
		}
		// If it's a WORD not used in redirection, store it for command creation
		else if (tokens->type == WORD && (!tokens->prev ||
				(tokens->prev->type != REDIR_IN && tokens->prev->type != REDIR_OUT &&
				tokens->prev->type != APPEND && tokens->prev->type != HEREDOC)))
			ft_lstadd_back(&word_list, ft_lstnew(ft_strdup(tokens->value)));
		// Handle redirection target (filename after <, >, etc.)
		else if (tokens->type == WORD && tokens->prev &&
				(tokens->prev->type == REDIR_IN || tokens->prev->type == REDIR_OUT ||
				tokens->prev->type == APPEND))
		{
			// Make sure current_cmd exists — create if needed
			if (!current_cmd && word_list)
			{
				current_cmd = create_cmd_from_list(word_list, env_list);
				add_cmd_back(args, current_cmd);
				args->cmd_count++;
				word_list = NULL;
			}
			if (!current_cmd)
			{
				current_cmd = ft_secure_malloc(sizeof(t_cmd));
				ft_bzero(current_cmd, sizeof(t_cmd));
				current_cmd->here_doc_fd = -1;
				add_cmd_back(args, current_cmd);
				args->cmd_count++;
			}
			add_file(current_cmd, tokens->value, tokens->prev->type);
		}
		tokens = tokens->next;
	}
	// If there are remaining command words after the last pipe
	if (word_list)
	{
		current_cmd = create_cmd_from_list(word_list, env_list);
		add_cmd_back(args, current_cmd);
		args->cmd_count++;
	}
	return (args);
}

void	print_cmd_list(t_args *args)
{
	t_cmd	*current_cmd;
	int		stage = 0;
	int		i;
	int		j;

	if (!args)
		return;

	printf("=== Parsing Summary ===\n");
	printf("Total commands: %d\n", args->cmd_count);
	printf("Total pipes   : %d\n", args->pipe);
	printf("Total here_doc   : %d\n", args->here_doc_count);
	if (args->limiter)
	{
		j = 0;
		while (args->limiter[j])
		{
			printf("[%d]Heredoc Limiter    : %s\n",j, args->limiter[j]);
			j++;
		}
	}
	current_cmd = args->cmd;
	while (current_cmd)
	{
		printf("=== Command %d ===\n", stage++);
		
		if (!current_cmd->cmd_tab || !current_cmd->cmd_tab[0])
			printf("  [empty command]\n");
		else
		{
			printf("Cmd tab: \n");
			i = 0;
			while (current_cmd->cmd_tab[i])
			{
				printf("Cmd tab[%d]: [%s]", i, current_cmd->cmd_tab[i]);
				if (current_cmd->sq && current_cmd->sq[i])
					printf(" (single quoted)");
				if (current_cmd->dq && current_cmd->dq[i])
					printf(" (double quoted)");
				printf("\n");
				i++;
			}
		}
		if (current_cmd->infile)
			printf("Input File         : %s\n",current_cmd->infile);
		if (current_cmd->outfile)
			printf("Output File        : %s\n", current_cmd->outfile);
		if (current_cmd->append_outfile)
			printf("Output File (>>): %s\n", current_cmd->append_outfile);
		current_cmd = current_cmd->next;
	}
	printf("=======================\n");
}


