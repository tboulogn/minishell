/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:39:55 by tboulogn          #+#    #+#             */
/*   Updated: 2025/03/31 17:02:36 by tboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*extract_word(char *input, int *i)
{
	int		start;
	char	quote;

	while (input[*i] && is_whitespace(input[*i])) // Skip spaces
		(*i)++;
	start = *i;
	quote = 0;
	while (input[*i] && (quote || (!is_whitespace(input[*i])
				&& !is_special_char(input[*i]))))
	{
		if (input[*i] == '"' || input[*i] == '\'')
		{
			if (quote == 0)
				quote = input[*i];  // Open quote
			else if (quote == input[*i])
				quote = 0;  // Close quote
		}
		else if (is_special_char(input[*i]) && !quote)
			break ;  // Stop if encountering `|`, `<`, `>` outside of quotes
		(*i)++;
	}
	return (ft_strndup(input + start, *i - start));
}

t_token	*tokenize(char *input)
{
	t_token	*tokens;
	int		i;

	tokens = NULL;//init t_token
	i = 0;
	while (input[i])
	{
		while (input[i] && is_whitespace(input[i]))//skip spaces
			i++;
		if (input[i] == '|')//detect pipe
		{
			add_token(&tokens, "|", PIPE);
			i++;
		}
		else if (input[i] == '>')
		{
			if (input[i + 1] == '>')//append output
			{
				add_token(&tokens, ">>", APPEND);
				i++;
			}
			else//non_append output
				add_token(&tokens, ">", REDIR_OUT);
			i++;
		}
		else if (input[i] == '<')
		{
			if (input[i + 1] == '<')//here_doc
			{
				add_token(&tokens, "<<", HEREDOC);
				i++;
			}
			else//normal redir_in
				add_token(&tokens, "<", REDIR_IN);
			i++;
		}
		else if (input[i])//Everything else is a word(cmd/filename/limiter)
			add_token(&tokens, extract_word(input, &i), WORD);
	}
	return (tokens);
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

//Initialize the argument infos we pass
t_args	*create_new_args(void)
{
	t_args	*new_args;

	new_args = ft_secure_malloc(sizeof(t_args));
	new_args->cmd_count = 0;
	// new_args->infile = NULL;
	// new_args->outfile = NULL;
	// new_args->append_outfile = NULL;
	new_args->limiter = NULL;
	new_args->here_doc_count = 0;
	new_args->pipe = 0;
	new_args->cmd = NULL;
	return (new_args);
}

// void add_cmd(t_args *args, char *word)
// {
// 	t_cmd *new;

// 	new = ft_secure_malloc(sizeof(t_cmd));
// 	new->cmd_tab = ft_split(args->cmd->cmd_path, ' ');
// 	new->next = NULL;
// 	new->prev = NULL;
// 	if (!args->cmd)
// 		args->cmd = new;
// 	else
// 	{
// 		t_cmd *tmp = args->cmd;
// 		while (tmp->next)
// 			tmp = tmp->next;
// 		tmp->next = new;
// 		new->prev = tmp;
// 	}
// 	args->cmd_count++;
// }

//to init t_cmd and set prev/next of t_cmd
void	add_cmd_back(t_args *args, t_cmd *new_cmd)
{
	t_cmd	*last;

	if (!args || !new_cmd)
		return ;
	new_cmd->next = NULL;
	new_cmd->prev = NULL;
	new_cmd->sq_count = 0;
	new_cmd->dq_count = 0;
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

int	count_char(char *str, char c)
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
	c_count = 0;
	while (s[i])
	{
		if (s[i] == c)
			c_count++;
		i++;
	}
	len = ft_strlen(s) - c_count;
	new_str = malloc(len + 1 * sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
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

// char	*modify_quates(char *str)
// {
// 	int		i;
// 	int		j;
// 	char	*modified;
	
// }


//set t_cmd cmd_tab by using t_list
t_cmd *create_cmd_from_list(t_list *words)
{
	t_cmd	*cmd;
	t_list	*tmp;
	int		count;
	int		i;
	
	cmd = ft_secure_malloc(sizeof(t_cmd));
	count = ft_lstsize(words);
	cmd->cmd_tab = ft_secure_malloc(sizeof(char *) * (count + 1));//+ 1 for NULL
	i = 0;
	while (words)
	{
		//check if there are quates
		// cmd->cmd_tab[i] = ft_strdup((char *)words->content);
		cmd->sq_count = count_char((char *)words->content, '\'');
		cmd->dq_count = count_char((char *)words->content, '"');
		// if (cmd->sq_count > 2)
		// {
		// 	cmd->dq_count = cmd->sq_count / 2;
		// 	cmd->sq_count = cmd->sq_count % 2;
		// }
		//change single quates into double if there are even number of them
		if (cmd->sq_count)
			cmd->cmd_tab[i] = ft_strdup_exept((char *)words->content, '\'');
		else if (cmd->dq_count)
			cmd->cmd_tab[i] = ft_strdup_exept((char *)words->content, '"');
		else
			cmd->cmd_tab[i] = ft_strdup((char *)words->content);
		tmp = words;
		words = words->next;
		free(tmp);
		i++;
	}
	cmd->cmd_tab[i] = NULL;
	cmd->cmd_path = NULL;
	return (cmd);
}

//change single quates into double if there are even number of them connected,
//count the quates, store them into the structure
//depending on the quate numbers, remove the quates from the string


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


t_args *parse_token(t_token *tokens)//store the argument info into t_args by using t_token
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
				current_cmd = create_cmd_from_list(word_list);
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
				current_cmd = create_cmd_from_list(word_list);
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
		current_cmd = create_cmd_from_list(word_list);
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
			printf("Cmd tab: ");
			i = 0;
			while (current_cmd->cmd_tab[i])
			{
				printf("[%s] ", current_cmd->cmd_tab[i]);
				i++;
			}
			printf("\n");
		}
		printf("singcle quote count %d\n", current_cmd->sq_count);
		printf("double quote count %d\n", current_cmd->dq_count);
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


