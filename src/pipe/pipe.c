/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:31:13 by ryada             #+#    #+#             */
/*   Updated: 2025/04/18 09:27:29 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	wait_children(t_args *args, t_pipe *pro)
{
	int	i;
	int	status;
	int	last_exit;

	i = 0;
	last_exit = 0;
	while (i < args->cmd_count)
	{
		waitpid(pro->pid[i], &status, 0);
		if (i++ == args->cmd_count - 1)
		{
			if (WIFEXITED(status))
				last_exit = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGQUIT)
					write(1, "Quit (core dumped)\n", 20);
				else if (WTERMSIG(status) == SIGINT)
					write(1, "\n", 1);
				last_exit = 128 + WTERMSIG(status);
			}
		}
	}
	g_signal = last_exit;
}

void	handle_pipe_and_fork(t_pipe	*pro, t_cmd *current, int i)
{
	if (current->next && pipe(pro->next) == -1)
	{
		perror("pipe");
		free(pro->pid);
		exit(EXIT_FAILURE);
	}
	pro->pid[i] = fork();
	if (pro->pid[i] == -1)
	{
		perror("fork");
		free(pro->pid);
		exit(EXIT_FAILURE);
	}
}

void	process_loop(t_args *args, t_env *env_list,
			t_pipe *pro, t_cmd	*current)
{
	t_args	*temp;
	int		i;

	i = 0;
	while (current)
	{
		temp = malloc(sizeof(t_args));
		init_temp_args(temp, current, args->cmd_count, i);
		handle_pipe_and_fork(pro, current, temp->index);
		if (pro->pid[i] == 0)
		{
			set_signal_child();
			child_process(temp, current, env_list, *pro);
		}
		free(temp);
		close_and_update(pro);
		current = current->next;
		i++;
	}
}

void	pipex(t_args *args, t_env **env_list)
{
	t_pipe	pro;
	t_cmd	*current;

	current = args->cmd;
	if (args->limiter && args->cmd_count == 0)
	{
		prepare_here_doc(args, current);
		return ;
	}
	if (!prepare_here_doc(args, current) && args->cmd_count == 1
		&& !ft_check_buildin(args) && no_files(current))
		return (ft_exec(args, env_list, &pro));
	init_pipe_struct(&pro, args->cmd_count);
	process_loop(args, *env_list, &pro, current);
	close_parent_pipes(&pro);
	signal(SIGINT, SIG_IGN);
	wait_children(args, &pro);
	init_signals();
	free(pro.pid);
}
