/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:45:30 by ryada             #+#    #+#             */
/*   Updated: 2025/04/08 17:59:10 by tboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//need to modify the prompt as the username, and exit etc
//need to fix a problem which exit the program after executing a cmd

char	*pwd_str(t_env *env_list)
{
	char	*pwd;
	char	*prompt;
	char	*user;
	char	*tmp;

	pwd = get_env_value(env_list, "PWD");
	user = get_env_value(env_list, "USER");// ->ryada
	tmp = ft_strjoin("/home/", user);// ->/home/ryada
	if (!tmp || !pwd)
		return (NULL);
	pwd = pwd + (ft_strlen(tmp));
	free (tmp);
	tmp = ft_strjoin(PROMPT, pwd);
	if (!tmp)
		return(NULL);
	prompt = ft_strjoin(tmp, "$ ");
	free(tmp);
	return (prompt);
}

void	put_prompt(char **input, t_env *env_list)
{
	char	*prompt;

	printf(">>> Prompt lance\n");
	prompt = pwd_str(env_list);
	*input = readline(prompt);
	free(prompt);
	if (!*input)
		return ;
	if (*input && **input)
		add_history(*input);
}

int	parsing(char *input, t_token **tokens, t_args **args, t_env *env_list)
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
	*args = parse_token(*tokens, env_list);
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
	char	*input;
	t_token	*tokens;
	t_args	*args;

	input = NULL;
	g_signal = 0;
	while (1)
	{
		init_signals();
		args = NULL;
		tokens = NULL;
		put_prompt(&input, *env_list);
		if (!input)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (parsing(input, &tokens, &args, *env_list))
		{
			if (args && args->cmd && args->cmd->cmd_tab
			&& ft_strcmp(args->cmd->cmd_tab[0], "exit") == 0)
				free_token(tokens);
			print_cmd_list(args);
			pipex(args, env_list);
		}
		if (args)
			free_cmd_list(args);
		if (tokens)
			free_token(tokens);
		free(input);
	}
	rl_clear_history();
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env_list;
	
	env_list = init_env_list(envp);
	if (ft_strncmp(argv[0], "./minishell", 11) == 0 && argc == 1)
		minishell(&env_list);
	else
	{
		ft_putstr_fd("Invalid program name or argument number\n", 2);
		free_env_list(env_list);
		return (1);
	}
	free_env_list(env_list);
	return (0);
}
