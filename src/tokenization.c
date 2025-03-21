/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:39:55 by tboulogn          #+#    #+#             */
/*   Updated: 2025/03/21 17:33:50 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// t_token	*tokenize(char *input)
// {
// 	t_token *tokens;
// 	int		i;

// 	tokens = NULL;//initialize as NULL
// 	i = 0;

// 	while (input[i])
// 	{
// 		if (input[i] == '|')
// 			add_token(&tokens, "|", PIPE);
// 		else if (input[i] == '>')
// 		{
// 			if (input[i + 1] == '>')
// 			{
// 				add_token(&tokens, ">>", APPEND);
// 				i++;
// 			}
// 			else
// 				add_token(&tokens, ">", REDIR_OUT);
// 		}
// 		else if (input[i] == '<')
// 		{
// 			if (input[i + 1] == '<')
// 			{
// 				add_token(&tokens, "<<", HEREDOC);
// 				i++;
// 			}
// 			else
// 				add_token(&tokens, "<", REDIR_IN);
// 		}
// 		else if (!is_whitespace(input[i]))
// 			add_token(&tokens, extract_word(input, &i), WORD);
// 		i++;
// 	}
// 	return (tokens);
// }

// void	add_token(t_token **tokens, char *value, t_token_type type)
// {
// 	t_token *new;
// 	t_token *tmp;

// 	new = ft_secure_malloc(sizeof(t_token));
// 	if (!new)
// 		return ;
// 	new->value = ft_strdup(value);
// 	new->type = type;
// 	new->next = NULL;
// 	if (!*tokens)
// 		*tokens = new;
// 	else
// 	{
// 		tmp = *tokens;
// 		while (tmp->next)
// 			tmp = tmp->next;
// 		tmp->next = new;
// 	}
// }

// char *extract_word(char *input, int *i)
// {
// 	int		start;
// 	int		len;
// 	char	quote;

// 	start = *i;
// 	len = 0;
// 	quote = 0;
// 	while(input[*i] && (quote || (!is_whitespace(input[*i]) && !is_special_char(input[*i]))))
// 	{
// 		if (input[*i] == '"' || input[*i] == '\'')
// 		{
// 			if (quote == 0)
// 				quote = input[*i];
// 			else if (quote == input[*i])
// 				quote = 0;
// 		}
// 		(*i)++;
// 		len++;
// 	}
// 	return (ft_strndup(input + start, len));	
// }
// //I guess we should have a function to set output, append etc as a helper unction
// t_cmd	*parse_token(t_token *tokens)
// {
// 	t_cmd *cmds;
// 	t_cmd *current;

// 	cmds = create_new_cmd();
// 	current = cmds;
// 	while (tokens)
// 	{
// 		if (tokens->type == WORD)
// 			add_arg_to_cmd(current, tokens->value);
// 		else if (tokens->type == REDIR_OUT)
// 			current->outfile = ft_strdup(tokens->next->value);
// 		else if (tokens->type == APPEND)
// 		{
// 			current->outfile = ft_strdup(tokens->next->value);
// 			current->append = 1;
// 		}
// 		else if (tokens->type == REDIR_IN)
// 			current->infile = ft_strdup(tokens->next->value);
// 		//else if (tokens->type == HEREDOC)
// 		//	handle_heredoc(current, tokens->next->value);
// 		else if (tokens->type == PIPE)
// 		{
// 			current->pipe = 1;
// 			current->next = create_new_cmd();
// 			current = current->next;
// 		}
// 		tokens = tokens->next;
// 	}
// 	return (cmds);
// }

// t_cmd *create_new_cmd(void)
// {
// 	t_cmd	*new_cmd;

// 	new_cmd = ft_secure_malloc(sizeof(t_cmd));
// 	new_cmd->infile = NULL;
// 	new_cmd->outfile = NULL;
// 	new_cmd->append = 0;
// 	new_cmd->pipe = 0;
// 	new_cmd->next = NULL;
// 	new_cmd->args = NULL;
// 	return (new_cmd);
// }

// void add_arg_to_cmd(t_cmd *cmd, char *arg)
// {
// 	int i;
// 	char **new_args;

// 	i = 0;
// 	while(cmd->args && cmd->args[i])
// 		i++;
// 	new_args = ft_secure_malloc(sizeof(char *) * (i + 2));
// 	i = 0;
// 	while (cmd->args && cmd->args[i])
// 	{
// 		new_args[i] = cmd->args[i];
// 		i++;
// 	}
// 	new_args[i] = ft_strdup(arg);
// 	new_args[i + 1] = NULL;
// 	if (cmd->args)
// 		free(cmd->args);
// 	cmd->args = new_args;
// }

// void print_cmd_list(t_cmd *cmd)
// {
//     int i;

//     while (cmd)
//     {
//         printf("=== Commande ===\n");
//         printf("Arguments : ");
//         i = 0;
//         while (cmd->args && cmd->args[i])
//         {
//             printf("[%s] ", cmd->args[i]);
//             i++;
//         }
//         printf("\n");

//         if (cmd->infile)
//             printf("Redirection entrée : %s\n", cmd->infile);
//         if (cmd->outfile)
//             printf("Redirection sortie : %s (%s)\n", cmd->outfile, cmd->append ? "append" : "overwrite");

//         printf("Pipe : %s\n", cmd->next ? "OUI" : "NON");
//         printf("================\n");

//         cmd = cmd->next;
//     }
// }

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
	// tokens->type = NULL;
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
				//add_token of "LIMITER"
			}
			else
				add_token(&tokens, "<", REDIR_IN);
			i++;
		}
		else if (input[i]) // Everything else is a word
			add_token(&tokens, extract_word(input, &i), WORD);
		// if (input[i]) 
		// 	i++; // Move forward only if not at end
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

//from tokens, we store infos into t_args
t_args *parse_token(t_token *tokens)
{
    t_args *args;
	
	args = create_new_args();

    while (tokens)
    {
        if (tokens->type == WORD && (!tokens->prev || (tokens->prev && tokens->prev->type != REDIR_IN && tokens->prev->type != REDIR_OUT)))//cmds or str
            add_cmds(args, tokens->value);
		else if (tokens->type == WORD && tokens->prev->type == REDIR_IN)//infile
			add_file(args, tokens->value, 0);
		else if (tokens->type == WORD && tokens->prev->type == REDIR_OUT)//outfile
			add_file(args, tokens->value, 1);
		// else if (tokens->type == REDIR_OUT && tokens->next)
		// 	set_output_file(args, tokens->next->value, 0);
		// else if (tokens->type == APPEND && tokens->next)
		// 	set_output_file(args, tokens->next->value, 1);
		// else if (tokens->type == REDIR_IN && tokens->next)
		// 	set_input_file(args, tokens->next->value);
		else if (tokens->type == PIPE)
			args->pipe++;
        tokens = tokens->next;
    }
    return (args);
}

//Initialize the argument infos we pass
t_args	*create_new_args(void)
{
	t_args	*new_args;

	new_args = ft_secure_malloc(sizeof(t_args));
	new_args->cmds = NULL;
	new_args->infile = NULL;
	new_args->outfile = NULL;
	new_args->pipe = 0;
	new_args->next = NULL;
	return (new_args);
}

void add_file(t_args *args, char *filename, int type)
{
	if (type == 0)
		args->infile = ft_strdup(filename);
	else if (type == 1)
		args->outfile = ft_strdup(filename);
}

void	add_cmds(t_args *args, char *cmd)
{
	int		i;
	int		j;
	char	**cmds;

	i = 0;
	while(args->cmds && args->cmds[i])
		i++;
	cmds = ft_secure_malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (args->cmds && args->cmds[i])
	{
		cmds[i] = ft_strdup(args->cmds[i]);
		i++;
	}
	if (cmds[i])
		free(cmds[i]);
	cmds[i] = ft_strdup(cmd);
	cmds[i + 1] = NULL;
	if (args->cmds)
	{
		j = 0;//we can call ft_free_tab here
		while (args->cmds[j])
		{
			free(args->cmds[j]);
			j++;
		}
		free(args->cmds);
	}
	args->cmds = cmds;
}

void print_cmd_list(t_args *args)
{
    int i;

	printf("=== Command ===\n");
	printf("Commands : ");
	i = 0;
	while (args->cmds && args->cmds[i])
	{
		printf("[%s]", args->cmds[i]);
		i++;
	}
	printf("\n");
	printf("============\n");
	// if (args->pipe > 0)
	// 	
	printf("Pipe count : %d\n", args->pipe);
	printf("============\n");
	if (args->infile)
        printf("Input File : %s\n", args->infile);
    if (args->outfile)
        printf("Output File : %s\n", args->outfile);
	// printf("\n");
}

