/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:45:30 by ryada             #+#    #+#             */
/*   Updated: 2025/03/19 19:26:40 by tboulogn         ###   ########.fr       */
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
	char		**copy_envi;
	t_token		*tokens;
	t_cmd		*cmd_list;
	t_env		*env;
	
	
	while (1)
	{
		input = readline(PROMPT);
		env = init_env_list(envp);
		copy_envi = copy_env(envp);
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
		ft_exec(copy_envi, cmd_list, env);

		free_cmd_list(cmd_list);
		free_token(tokens);
		free(input);
	}
}



int main(int argc, char **argv, char **envp)
{
	put_prompt(envp);
	return (0);
}