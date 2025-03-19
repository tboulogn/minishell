/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:39:55 by tboulogn          #+#    #+#             */
/*   Updated: 2025/03/19 13:39:27 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*tokenize(char *input)
{
	t_token *tokens;
	int		i;

	tokens = NULL;
	i = 0;

	while (input[i])
	{
		if (input[i] == '|')
			add_token(&tokens, "|", PIPE);
		else if (input[i] == '>')
		{
			if (input[i + 1] == '>')
			{
				add_token(&tokens, ">>", APPEND);
				i++;
			}
			else
				add_token(&tokens, ">", REDIR_OUT);
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
		}
		else if (!is_whitespace(input[i]))
			add_token(&tokens, extract_word(input, &i), WORD);
		i++;
	}
	return (tokens);
}

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
	if (!*tokens)
		*tokens = new;
	else
	{
		tmp = *tokens;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

char *extract_word(char *input, int *i)
{
	int		start;
	int		len;
	char	quote;

	start = *i;
	len = 0;
	quote = 0;
	while(input[*i] && (quote || (!is_whitespace(input[*i]) && !is_special_char(input[*i]))))
	{
		if (input[*i] == '"' || input[*i] == '\'')
		{
			if (quote == 0)
				quote = input[*i];
			else if (quote == input[*i])
				quote = 0;
		}
		(*i)++;
		len++;
	}
	return (ft_strndup(input + start, len));	
}
//I guess we should have a function to set output, append etc as a helper unction
t_cmd	*parse_token(t_token *tokens)
{
	t_cmd *cmds;
	t_cmd *current;

	cmds = create_new_cmd();
	current = cmds;
	while (tokens)
	{
		if (tokens->type == WORD)
			add_arg_to_cmd(current, tokens->value);
		else if (tokens->type == REDIR_OUT)
			current->outfile = ft_strdup(tokens->next->value);
		else if (tokens->type == APPEND)
		{
			current->outfile = ft_strdup(tokens->next->value);
			current->append = 1;
		}
		else if (tokens->type == REDIR_IN)
			current->infile = ft_strdup(tokens->next->value);
		//else if (tokens->type == HEREDOC)
		//	handle_heredoc(current, tokens->next->value);
		else if (tokens->type == PIPE)
		{
			current->pipe = 1;
			current->next = create_new_cmd();
			current = current->next;
		}
		tokens = tokens->next;
	}
	return (cmds);
}

t_cmd *create_new_cmd(void)
{
	t_cmd	*new_cmd;

	new_cmd = ft_secure_malloc(sizeof(t_cmd));
	new_cmd->infile = NULL;
	new_cmd->outfile = NULL;
	new_cmd->append = 0;
	new_cmd->pipe = 0;
	new_cmd->next = NULL;
	new_cmd->args = NULL;
	return (new_cmd);
}

void add_arg_to_cmd(t_cmd *cmd, char *arg)
{
	int i;
	char **new_args;

	i = 0;
	while(cmd->args && cmd->args[i])
		i++;
	new_args = ft_secure_malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (cmd->args && cmd->args[i])
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	new_args[i] = ft_strdup(arg);
	new_args[i + 1] = NULL;
	if (cmd->args)
		free(cmd->args);
	cmd->args = new_args;
}

void print_cmd_list(t_cmd *cmd)
{
    int i;

    while (cmd)
    {
        printf("=== Commande ===\n");
        printf("Arguments : ");
        i = 0;
        while (cmd->args && cmd->args[i])
        {
            printf("[%s] ", cmd->args[i]);
            i++;
        }
        printf("\n");

        if (cmd->infile)
            printf("Redirection entrée : %s\n", cmd->infile);
        if (cmd->outfile)
            printf("Redirection sortie : %s (%s)\n", cmd->outfile, cmd->append ? "append" : "overwrite");

        printf("Pipe : %s\n", cmd->next ? "OUI" : "NON");
        printf("================\n");

        cmd = cmd->next;
    }
}
