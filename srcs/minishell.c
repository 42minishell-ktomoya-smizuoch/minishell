/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smizuoch <smizuoch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:50:09 by ktomoya           #+#    #+#             */
/*   Updated: 2023/09/02 11:52:23 by smizuoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	main(int argc, char **argv)
// {
// 	if (argc < 2)
// 		return (FAILURE);
// //	display_prompt();
// 	// launch_executable((const char *)argv[1]);
// 	return (SUCCESS);
// }

int	main()
{
	t_token		*tokens;
	t_token		*current;
	const char	*command;

	const char *command = "echo \"Hello,\"\' world!\'";
	while (1)
	{
		command = readline("minishell$ ");
		tokens = tokenize(command);
		current = tokens;
		while (current != NULL)
		{
			printf("Token: %s, Type: %d, State: %d\n", current->word, current->type, current->state);
			current = current->next;
		}
		free ((void *)command);
	}
	return (0);
}
