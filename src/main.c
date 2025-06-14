/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:45:30 by ryada             #+#    #+#             */
/*   Updated: 2025/04/18 09:30:00 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*pwd_str(t_env *env_list)
{
	char	*pwd;
	char	*prompt;
	char	*user;
	char	*tmp;

	pwd = get_env_value(env_list, "PWD");
	user = get_env_value(env_list, "USER");
	tmp = ft_strjoin("/home/", user);
	if (!tmp || !pwd)
		return (NULL);
	pwd = pwd + (ft_strlen(tmp));
	free (tmp);
	tmp = ft_strjoin(PROMPT, pwd);
	if (!tmp)
		return (NULL);
	prompt = ft_strjoin(tmp, "$ ");
	free(tmp);
	return (prompt);
}

void	put_prompt(char **input, t_env *env_list)
{
	char	*prompt;

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
		return (0);
	if (!check_syntax_error(*tokens))
	{
		free_token(*tokens);
		tokens = NULL;
		return (0);
	}
	*args = parse_token(*tokens, env_list);
	if (!*args)
	{
		free_token(*tokens);
		tokens = NULL;
		if (*args)
		{
			free_cmd_list(*args);
			*args = NULL;
		}
		return (0);
	}
	return (1);
}

void	minishell(t_env **env_list)
{
	char	*input;

	input = NULL;
	g_signal = 0;
	init_signals();
	while (1)
	{
		put_prompt(&input, *env_list);
		if (!input)
		{
			write(1, "exit\n", 5);
			break ;
		}
		parse_and_exec(input, env_list);
		free(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env_list;
	char	*lvl_str;
	char	*new_lvl;
	int		shlvl;

	env_list = init_env_list(envp);
	lvl_str = get_env_value(env_list, "SHLVL");
	if (lvl_str)
		shlvl = ft_atoi(lvl_str) + 1;
	else
		shlvl = 1;
	new_lvl = ft_itoa(shlvl);
	set_env_value(&env_list, "SHLVL", new_lvl);
	free(new_lvl);
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
