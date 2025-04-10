/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:15:32 by tboulogn          #+#    #+#             */
/*   Updated: 2025/04/10 13:52:01 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//everytime you finish the execution, free EVERYTHING!!

void	free_token(t_token *tokens)
{
	t_token	*next_token;

	while (tokens)
	{
		next_token = tokens->next;
		free(tokens->value);
		free(tokens);
		tokens = next_token;
	}
}

// void	free_t_cmd(t_cmd *cmds)
// {
// 	t_cmd	*next_cmd;
// 	int		i;

// 	next_cmd = cmds->next;
// 	while(cmds)
// 	{
// 		if (cmds->cmd_tab)
// 			free_env_array(cmds->cmd_tab);
// 		if (cmds->sq)
// 			free(cmds->sq);
// 		if (cmds->dq)
// 			free(cmds->dq);
// 		if (cmds->cmd_path)
// 			free(cmds->cmd_path);
// 		if (cmds->infile)
// 			free(cmds->infile);
// 		if (cmds->outfile)
// 			free(cmds->outfile);
// 		if (cmds->append_outfile)
// 			free(cmds->append_outfile);
// 		free(cmds);
// 		cmds = next_cmd;
// 		next_cmd = cmds->next;
// 	}
// }

// void	free_cmd_list(t_args *args)
// {
// 	free_t_cmd(args->cmd);
// 	if (args->limiter)
// 		free_env_array(args->limiter);
// 	if (args)
// 		free(args);
// }

void	free_cmd_list(t_args *args)
{
	t_cmd	*tmp_cmd;
	t_cmd	*next_cmd;
	int		i;

	if (!args)
		return ;
	tmp_cmd = args->cmd;
	while (tmp_cmd)
	{
		next_cmd = tmp_cmd->next;
		if (tmp_cmd->cmd_tab)
		{
			i = 0;
			while (tmp_cmd->cmd_tab[i])
				free(tmp_cmd->cmd_tab[i++]);
			free(tmp_cmd->cmd_tab);
		}
		if (tmp_cmd->sq)
			free(tmp_cmd->sq);
		if (tmp_cmd->dq)
			free(tmp_cmd->dq);
		if (tmp_cmd->cmd_path)
			free(tmp_cmd->cmd_path);
		if (tmp_cmd->infile)
			free(tmp_cmd->infile);
		if (tmp_cmd->outfile)
			free(tmp_cmd->outfile);
		if (tmp_cmd->append_outfile)
			free(tmp_cmd->append_outfile);
		free(tmp_cmd);
		tmp_cmd = next_cmd;
	}
	free_env_array(args->limiter);
	free(args);
}

void	free_env_array(char **env_array)
{
	int	i;

	if (!env_array)
		return ;
	i = 0;
	while (env_array[i])
	{
		free(env_array[i]);
		i++;
	}
	free(env_array);
}

void	free_env_node(t_env *node)
{
	if (!node)
		return ;
	free(node->key);
	free(node->value);
	free(node);
}

void	free_env_list(t_env *env)
{
	t_env	*tmp;
	
	while (env)
	{
		tmp = env->next;
		if (env->key)
			free(env->key);
		if (env->value)
			free(env->value);
		free(env);
		env = tmp;
	}
}

void	ft_free_cmd(t_cmd *cmd)
{
	int	i;
	
	i = 0;
	if (!cmd)
		return ;
	if (cmd->cmd_tab)
	{
		while(cmd->cmd_tab[i])
			free(cmd->cmd_tab[i++]);
		free(cmd->cmd_tab);
	}
	if (cmd->sq)
		free(cmd->sq);
	if (cmd->dq)
		free(cmd->dq);
	free(cmd);
}

void	free_ereaser(t_args *args, t_env *env)
{
	free_cmd_list(args);
	free_env_list(env);
}