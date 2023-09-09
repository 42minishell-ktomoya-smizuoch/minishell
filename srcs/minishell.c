/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:50:09 by ktomoya           #+#    #+#             */
/*   Updated: 2023/09/09 17:52:11 by ktomoya          ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	t_token		*tokens;
	t_token		*current;
	const char	*line;

	(void)argv;
	if (argc != 1)
		return (FAILURE);
	while (1)
	{
		line = readline("minishell$ ");
		if (*line)
			add_history(line);
		tokens = lexer(line);
		current = tokens;
		while (current != NULL)
		{
			printf("Token: %s, Type: %d\n", current->word, current->type);
			current = current->next;
		}
		free ((void *)line);
	}
	return (0);
}
