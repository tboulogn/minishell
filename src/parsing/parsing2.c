/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:39:55 by tboulogn          #+#    #+#             */
/*   Updated: 2025/04/18 09:59:26 by tboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*create_cmd_from_list(t_list *words, t_env *env_list)
{
	t_cmd	*cmd;
	int		i;
	t_list	*next;
	char	*cleaned;

	cmd = ft_calloc(1, sizeof(t_cmd));
	i = ft_lstsize(words);
	cmd->cmd_tab = ft_calloc(i + 1, sizeof(char *));
	cmd->sq = ft_calloc(i, sizeof(bool));
	cmd->dq = ft_calloc(i, sizeof(bool));
	i = 0;
	while (words)
	{
		next = words->next;
		cleaned = update_quotes_and_clean(words->content,
				&cmd->sq[i], &cmd->dq[i]);
		if (!cmd->sq[i])
			cleaned = expand_if_needed(cleaned, env_list, cmd);
		cmd->cmd_tab[i++] = cleaned;
		free(words->content);
		free(words);
		words = next;
	}
	cmd->cmd_tab[i] = NULL;
	return (cmd);
}

void	parse_last_cmd(t_list **word_list, t_cmd **current_cmd,
			t_args *args, t_env *env_list)
{
	if (word_list)
	{
		*current_cmd = create_cmd_from_list(*word_list, env_list);
		add_cmd_back(args, *current_cmd);
		args->cmd_count++;
	}
}

t_args	*parse_token(t_token *tokens, t_env *env)
{
	t_args	*args;
	t_cmd	*cur_cmd;
	t_list	*word;
	int		parse_type;

	args = create_new_args();
	cur_cmd = NULL;
	word = NULL;
	while (tokens)
	{
		parse_type = parsing_type(tokens);
		if ((parse_type == 1 && !parse_pipe(args, &cur_cmd, env, &word))
			|| (parse_type == 4 && !parse_redir(args, &cur_cmd, env, &word)))
			return (NULL);
		if (parse_type == 2)
		{
			parse_here_doc(tokens, args);
			tokens = tokens->next;
		}
		else if (parse_type == 3)
			ft_lstadd_back(&word, ft_lstnew(ft_strdup(tokens->value)));
		if (parse_type == 4)
			add_file(cur_cmd, tokens->value, tokens->prev->type);
		tokens = tokens->next;
	}
	if (word)
		parse_last_cmd(&word, &cur_cmd, args, env);
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
