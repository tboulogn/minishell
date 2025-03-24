/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:39:55 by tboulogn          #+#    #+#             */
/*   Updated: 2025/03/22 17:00:12 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *extract_word(char *input, int *i)
{
	int		start;
	char	quote;

	while (input[*i] && is_whitespace(input[*i])) // Skip spaces
		(*i)++;

	start = *i;
	quote = 0;

	while (input[*i] && (quote || (!is_whitespace(input[*i]) && !is_special_char(input[*i]))))
	{
		if (input[*i] == '"' || input[*i] == '\'')
		{
			if (quote == 0)
				quote = input[*i];  // Open quote
			else if (quote == input[*i])
				quote = 0;  // Close quote
		}
		else if (is_special_char(input[*i]) && !quote)
			break;  // Stop if encountering `|`, `<`, `>` outside of quotes

		(*i)++;
	}
	return ft_strndup(input + start, *i - start);
}

void init_token(t_token *tokens)
{
	tokens->next = NULL;
	tokens->prev = NULL;
	tokens->value = NULL;
	tokens = NULL;
}

t_token	*tokenize(char *input)
{
	t_token *tokens;
	int		i;

	// init_token(tokens);
	tokens = NULL;
	i = 0;
	while (input[i])
	{
		while (input[i] && is_whitespace(input[i]))  // Skip spaces
			i++;
		if (input[i] == '|') // Detect pipe without needing spaces
		{
			add_token(&tokens, "|", PIPE);
			i++;
		} 
		else if (input[i] == '>')
		{
			if (input[i + 1] == '>')
			{
				add_token(&tokens, ">>", APPEND);
				// printf("YES THERE IS APPEND\n");
				i++;
			}
			else
				add_token(&tokens, ">", REDIR_OUT);
			i++;
		}
		else if (input[i] == '<')
		{
			if (input[i + 1] == '<')
			{
				add_token(&tokens, "<<", HEREDOC);
				i++;
			}
			else
				add_token(&tokens, "<", REDIR_IN);
			i++;
		}
		else if (input[i]) // Everything else is a word
			add_token(&tokens, extract_word(input, &i), WORD);
	}
	return (tokens);
}


//set up the next/cahin-list and types
void	add_token(t_token **tokens, char *value, t_token_type type)
{
	t_token *new;
	t_token *tmp;

	new = ft_secure_malloc(sizeof(t_token));
	if (!new)
		return ;
	new->value = ft_strdup(value);
	new->type = type;
	new->next = NULL;
	new->prev = NULL;

	if (!*tokens)
		*tokens = new;
	else
	{
		tmp = *tokens;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
}

//Initialize the argument infos we pass
t_args	*create_new_args(void)
{
	t_args	*new_args;

	new_args = ft_secure_malloc(sizeof(t_args));
	new_args->cmd_count = 0;
	new_args->infile = NULL;
	new_args->outfile = NULL;
	new_args->append_outfile = NULL;
	new_args->limiter = NULL;
	new_args->pipe = 0;
	return (new_args);
}

void add_cmd(t_args *args, char *word)
{
	t_cmd *new;

	new = ft_secure_malloc(sizeof(t_cmd));
	new->cmd_tab = ft_split(args->cmd->cmd_path, ' ');
	new->next = NULL;
	new->prev = NULL;
	if (!args->cmd)
		args->cmd = new;
	else
	{
		t_cmd *tmp = args->cmd;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
	args->cmd_count++;
}

void	add_cmd_back(t_args *args, t_cmd *new_cmd)
{
	t_cmd	*last;

	if (!args || !new_cmd)
		return;
	if (!args->cmd)
	{
		args->cmd = new_cmd;
		return;
	}
	last = args->cmd;
	while (last->next)
		last = last->next;
	last->next = new_cmd;
	new_cmd->prev = last;
}


t_cmd *create_cmd_from_list(t_list *words)
{
	t_cmd *cmd = ft_secure_malloc(sizeof(t_cmd));
	int count = ft_lstsize(words);
	cmd->cmd_tab = ft_secure_malloc(sizeof(char *) * (count + 1));
	cmd->prev = NULL;
	cmd->next = NULL;

	int i = 0;
	while (words)
	{
		cmd->cmd_tab[i++] = words->content;
		t_list *tmp = words;
		words = words->next;
		free(tmp);
	}
	cmd->cmd_tab[i] = NULL;
	cmd->cmd_path = NULL;
	return cmd;
}


//from tokens, we store infos into t_args
// t_args *parse_token(t_token *tokens)
// {
// 	t_args *args;
// 	t_args *head;
// 	int		cmd_total;

// 	args = create_new_args();
// 	head = args;
// 	cmd_total = 1;
// 	while (tokens)
// 	{
// 		if (tokens->type == PIPE)
// 		{
// 			args->pipe = 1;
// 			args->next = create_new_args();
// 			args = args->next;
// 			cmd_total++;
// 			tokens = tokens->next;
// 			continue;
// 		}
// 		if (tokens->prev && tokens->prev->type == HEREDOC)
// 			args->limiter = ft_strdup(tokens->value);
// 		else if (tokens->type == WORD && tokens->prev && tokens->prev->type == APPEND)
// 			add_file(args, tokens->value, 2);
// 		else if (tokens->type == WORD && tokens->prev && tokens->prev->type == REDIR_IN)
// 			add_file(args, tokens->value, 0);
// 		else if (tokens->type == WORD && tokens->prev && tokens->prev->type == REDIR_OUT)
// 			add_file(args, tokens->value, 1);
// 		else if (tokens->type == WORD)
// 			add_cmd(args, tokens->value);
// 		tokens = tokens->next;
// 	}
// 	head->cmd_count = cmd_total;
// 	return head;
// }

t_args *parse_token(t_token *tokens)
{
	t_args *args;
	t_cmd *current_cmd;
	t_list *word_list;
	t_cmd *new_cmd;
	t_cmd *final_cmd;

	args = create_new_args();
	current_cmd = NULL;
	word_list = NULL;
	args->cmd_count = 0;
	args->pipe = 0;
	while (tokens)
	{
		if (tokens->type == PIPE)
		{
			new_cmd = create_cmd_from_list(word_list);
			add_cmd_back(args, new_cmd);
			word_list = NULL;
			args->pipe++;
			args->cmd_count++;
			tokens = tokens->next;
			continue;
		}
		else if (tokens->type == WORD && (!tokens->prev || (
			tokens->prev->type != REDIR_IN && tokens->prev->type != REDIR_OUT &&
			tokens->prev->type != APPEND && tokens->prev->type != HEREDOC)))
		{
			ft_lstadd_back(&word_list, ft_lstnew(ft_strdup(tokens->value)));
		}
		else if (tokens->type == WORD && tokens->prev->type == REDIR_IN)
			args->infile = ft_strdup(tokens->value);
		else if (tokens->type == WORD && tokens->prev->type == REDIR_OUT)
			args->outfile = ft_strdup(tokens->value);
		else if (tokens->type == WORD && tokens->prev->type == APPEND)
			args->append_outfile = ft_strdup(tokens->value);
		else if (tokens->type == WORD && tokens->prev->type == HEREDOC)
			args->limiter = ft_strdup(tokens->value);
		tokens = tokens->next;
	}
	if (word_list)
	{
		final_cmd = create_cmd_from_list(word_list);
		add_cmd_back(args, final_cmd);
		args->cmd_count++;
	}
	return args;
}


// t_args *parse_token(t_token *tokens)
// {
// 	t_args *args;
// 	t_args *head;
// 	int		cmd_total;
// 	int		pipe_total;

// 	cmd_total = 1;
// 	pipe_total = 0;
// 	args = create_new_args();
// 	head = args;
// 	while (tokens)
// 	{
// 		if (tokens->type == PIPE)
// 		{
// 			args->pipe = 1;
// 			args->next = create_new_args();
// 			args = args->next;
// 			cmd_total++;
// 			pipe_total++;
// 			tokens = tokens->next;
// 			continue;
// 		}
// 		if (tokens->prev && tokens->prev->type == HEREDOC)
// 			args->limiter = ft_strdup(tokens->value);
// 		else if (tokens->type == WORD && tokens->prev && tokens->prev->type == APPEND)
// 			add_file(args, tokens->value, 2);
// 		else if (tokens->type == WORD && tokens->prev && tokens->prev->type == REDIR_IN)
// 			add_file(args, tokens->value, 0);
// 		else if (tokens->type == WORD && tokens->prev && tokens->prev->type == REDIR_OUT)
// 			add_file(args, tokens->value, 1);
// 		else if (tokens->type == WORD)
// 			add_cmd(args, tokens->value);
// 		tokens = tokens->next;
// 	}
// 	head->cmd_count = cmd_total;
// 	head->pipe = pipe_total;
// 	return head;
// }


void add_file(t_args *args, char *filename, int type)
{
	if (type == 0)
		args->infile = ft_strdup(filename);
	else if (type == 1)
		args->outfile = ft_strdup(filename);
	else if (type == 2)
		args->append_outfile = ft_strdup(filename);
}

// void print_cmd_list(t_args *args)
// {
//     int i;
// 	t_cmd *cmd;

// 	printf("=== Command ===\n");
// 	printf("Cmd count : %d\n", args->cmd_count);
// 	cmd = args->cmd;
// 	printf("Commands: ");
// 	while (cmd)
// 	{
// 		printf("[%s] ", cmd->cmd_name);
// 		cmd = cmd->next;
// 	}
// 	printf("\n");
// 	printf("============\n");
// 	printf("Pipe count : %d\n", args->pipe);
// 	printf("============\n");
// 	if (args->infile)
//         printf("Input File : %s\n", args->infile);
// 	if (args->limiter)
//         printf("Limiter : %s\n", args->limiter);
//     if (args->outfile)
//         printf("Output File : %s\n", args->outfile);
// 	if (args->append_outfile)
//         printf("Output File(append) : %s\n", args->append_outfile);
// 	printf("============\n");
// 	// printf("\n");
// }

// void print_cmd_list(t_args *args)
// {
// 	int		i;
// 	t_cmd	*cmd;
// 	int		stage;

// 	stage = 0;
// 	while (args)
// 	{
// 		printf("=== Command %d ===\n", stage);
// 		printf("Cmd count : %d\n", args->cmd_count);
// 		cmd = args->cmd;
// 		printf("Commands: ");
// 		i = 0;
// 		while (cmd)
// 		{
// 			printf("[%s] ", cmd->cmd_name);
// 			cmd = cmd->next;
// 		}
// 		printf("\n");
// 		printf("Pipe to next : %s\n", args->pipe ? "YES" : "NO");
// 		if (args->infile)
// 			printf("Input File : %s\n", args->infile);
// 		if (args->limiter)
// 			printf("Limiter : %s\n", args->limiter);
// 		if (args->outfile)
// 			printf("Output File : %s\n", args->outfile);
// 		if (args->append_outfile)
// 			printf("Output File(append) : %s\n", args->append_outfile);
// 		printf("============\n\n");
// 		args = args->next;
// 		stage++;
// 	}
// }


void print_cmd_list(t_args *args)
{
	t_cmd *cmd;
	int		stage = 0;
	int		i;

	if (!args)
		return;

	printf("=== Parsing Summary ===\n");
	printf("Total commands: %d\n", args->cmd_count);
	printf("Total pipes   : %d\n", args->pipe);
	if (args->infile)
		printf("Input File         : %s\n", args->infile);
	if (args->limiter)
		printf("Heredoc Limiter    : %s\n", args->limiter);
	if (args->outfile)
		printf("Output File        : %s\n", args->outfile);
	if (args->append_outfile)
		printf("Output File (>>): %s\n", args->append_outfile);
	printf("=======================\n\n");

	cmd = args->cmd;
	while (cmd)
	{
		printf("=== Command %d ===\n", stage++);
		if (!cmd->cmd_tab || !cmd->cmd_tab[0])
			printf("  [empty command]\n");
		else
		{
			printf("  cmd tab: ");
			i = 0;
			while (cmd->cmd_tab[i])
			{
				printf("[%s] ", cmd->cmd_tab[i]);
				i++;
			}
			printf("\n");
		}
		cmd = cmd->next;
	}
	printf("=======================\n");
}


