/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:50:09 by ktomoya           #+#    #+#             */
/*   Updated: 2023/09/02 19:10:05 by ktomoya          ###   ########.fr       */
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

	while (1)
	{
		command = readline("minishell$ ");
		tokens = tokenize(command);
		current = tokens;
		while (current != NULL)
		{
			printf("Token: %s, Type: %d\n", current->word, current->type);
			current = current->next;
		}
		free ((void *)command);
	}
	return (0);
}
