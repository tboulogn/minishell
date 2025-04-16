/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:39:55 by tboulogn          #+#    #+#             */
/*   Updated: 2025/04/15 17:21:36 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	find_char_pos(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}

void	add_file(t_cmd *cmd, char *str, t_token_type type)
{
	if (!cmd || !str)
		return ;
	if (type == REDIR_IN)
		cmd->infile = ft_strdup(str);
	else if (type == REDIR_OUT)
		cmd->outfile = ft_strdup(str);
	else if (type == APPEND)
		cmd->append_outfile = ft_strdup(str);
}

void	add_malloc_line(char ***arr, char *line)
{
	int		i;
	char	**new_arr;

	i = 0;
	if (!*arr)
		return (first_limitter(arr, line));
	while ((*arr)[i])
		i++;
	new_arr = malloc(sizeof(char *) * (i + 2));
	if (!new_arr)
		return ;
	i = 0;
	while ((*arr)[i])
	{
		new_arr[i] = (*arr)[i];
		i++;
	}
	new_arr[i] = ft_strdup(line);
	new_arr[i + 1] = NULL;
	free(*arr);
	*arr = new_arr;
}
