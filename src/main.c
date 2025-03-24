/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:45:30 by ryada             #+#    #+#             */
/*   Updated: 2025/03/24 16:21:25 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//need to modify the prompt as the username, and exit etc
//need to fix a problem which exit the program after executing a cmd

void	put_prompt(char **input)
{
	*input = readline(PROMPT);
	if (!*input)
		printf("exit\n");
	if (**input)
		add_history(*input);
}

void parsing(char *input, t_token **tokens, t_args **args)
{
	*tokens = tokenize(input);
	if (!*tokens)
	{
		free(input);
		return;
	}
	if (!check_syntax_error(*tokens))
	{
		free_token(*tokens);
		free(input);
		return;
	}
	*args = parse_token(*tokens);
	if (!*args)
	{
		free_token(*tokens);
		free(input);
	}
}

void	minishell(t_env *env_list)
{
	char		*input;
	t_token		*tokens;
	t_args		*args;

	input = NULL;
	while (1)
	{
		put_prompt(&input);
		parsing(input, &tokens, &args);
		print_cmd_list(args);
		// if (args->cmd_count > 1)
			pipex(args, env_list);
		// else
		// 	ft_exec(args, env_list);
		if (args)
			free_cmd_list(args);
		if (tokens)
			free_token(tokens);
		if (input)
			free(input);
	}
	
}

int main(int argc, char **argv, char **envp)
{
	t_env	*env_list;

	env_list = init_env_list(envp);
	// if (ft_strncmp(argv[0], "./minishell", 11) == 0 && argc == 1)
		minishell(env_list);
	// else
	// {
	// 	ft_putstr_fd("Invalid program name or argument number\n", 2);
	// 	return (1);
	// }
	// if (args)
	// 		free_cmd_list(args);
	return (0);
}