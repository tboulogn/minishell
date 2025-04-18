/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:06:31 by tboulogn          #+#    #+#             */
/*   Updated: 2025/04/18 11:05:15 by tboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redirect_and_close(int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) == -1)
	{
		perror("dup2");
		close(old_fd);
		return (-1);
	}
	return (close(old_fd));
}

int	is_number(const char *str)
{
	if (!str)
		return (0);
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (!isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

long long	ft_atoll(const char *str)
{
	int	sign;
	int	result;

	sign = 1;
	result = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str++ == '-')
			sign = -sign;
	}
	while (*str && isdigit(*str))
		result = result * 10 + (*str++ - '0');
	return (result * sign);
}

char	*expand_vars(const char *str, t_env *env_list, int i)
{
	char	*res;
	char	*chunk;
	char	*tmp;

	res = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != '\0')
		{
			i++;
			chunk = expand_dollar(str, &i, env_list, -1);
		}
		else if (str[i] == '$')
		{
			i++;
			chunk = ft_strdup("$");
		}
		else
			chunk = extract_text(str, &i);
		tmp = res;
		res = ft_strjoin(res, chunk);
		free(chunk);
		free(tmp);
	}
	return (res);
}

void	parse_and_exec(char *input, t_env **env_list)
{
	t_token	*tokens;
	t_args	*args;

	tokens = NULL;
	args = NULL;
	if (!parsing(input, &tokens, &args, *env_list))
		return ;
	print_cmd_list(args);
	if (tokens)
		free_token(tokens);
	pipex(args, env_list);
	if (args)
		free_cmd_list(args);
}
