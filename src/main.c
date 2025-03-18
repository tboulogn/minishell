/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:45:30 by ryada             #+#    #+#             */
/*   Updated: 2025/03/18 15:02:52 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//need to modify the prompt as the username, and exit etc
//this is just an example
void	put_prompt()
{
	char	*input;

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
		printf("You entered: %s\n", input);
		free(input);
	}
}

int main(void)
{
	put_prompt();
	return (0);
}