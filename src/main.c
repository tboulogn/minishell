/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:45:30 by ryada             #+#    #+#             */
/*   Updated: 2025/03/19 14:01:54 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//need to modify the prompt as the username, and exit etc
//this is just an example
//we are doing too many things in this function
//need to fix a problem which exit the program after executing a cmd
void	put_prompt(char **envp)
{
	char		*input;
	t_token		*tokens;
	t_cmd		*cmd_list;

	while (1)
	{
		input = readline(PROMPT);
		if (!input)
		{
			printf("exit\n");
			break;
		}
		if (*input)
			add_history(input);

		tokens = tokenize(input);
		if (!tokens)
		{
			free(input);
			continue;
		}

		cmd_list = parse_token(tokens);
		if (!cmd_list)
		{
			free_token(tokens);
			free(input);
			continue;
		}

		print_cmd_list(cmd_list);
		ft_exec(envp, cmd_list);

		free_cmd_list(cmd_list);
		put_prompt(envp);
		free_token(tokens);
		free(input);
	}
}

int main(int argc, char **argv, char **envp)
{
	put_prompt(envp);
	return (0);
}