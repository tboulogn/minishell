/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:45:30 by ryada             #+#    #+#             */
/*   Updated: 2025/03/29 14:29:31 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//need to modify the prompt as the username, and exit etc
//need to fix a problem which exit the program after executing a cmd

char	*pwd_str(t_env *env_list)
{
	char	*pwd;
	char	*prompt;
	char 	*user;

	pwd = get_env_value(env_list, "PWD");
	user = get_env_value(env_list, "USER");// ->ryada
	user = ft_strjoin("/home/", user);// ->/home/ryada
	pwd = pwd + (ft_strlen(user));
	prompt = ft_strjoin(PROMPT, pwd);
	prompt = ft_strjoin(prompt, "$ ");
	if (!pwd)
		return (NULL);
	return (prompt);	
}

void	put_prompt(char **input, t_env *env_list)
{
	char *prompt;

	prompt = pwd_str(env_list);
	*input = readline(prompt);
	if (!*input)
		printf("exit\n");
	if (**input)
		add_history(*input);
}

int parsing(char *input, t_token **tokens, t_args **args)
{
	*tokens = tokenize(input);
	if (!*tokens)
	{
		free(input);
		return (0);
	}
	if (!check_syntax_error(*tokens))
	{
		free_token(*tokens);
		tokens = NULL;
		free(input);
		return (0);
	}
	*args = parse_token(*tokens);
	if (!*args)
	{
		free_token(*tokens);
		tokens = NULL;
		free(input);
		return (0);
	}
	return (1);
}


void	minishell(t_env **env_list)
{
	char		*input;
	t_token		*tokens;
	t_args		*args;

	input = NULL;
	while (1)
	{
		put_prompt(&input, *env_list);
		if (parsing(input, &tokens, &args))
		{
			print_cmd_list(args);
			pipex(args, env_list);
		}
		else
			continue;
		// ft_exec(args, env_list);
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
	if (ft_strncmp(argv[0], "./minishell", 11) == 0 && argc == 1)
		minishell(&env_list);
	else
	{
		ft_putstr_fd("Invalid program name or argument number\n", 2);
		return (1);
	}
	// if (args)
	// 		free_cmd_list(args);
	return (0);
}