/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kudoutomoya <kudoutomoya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:50:09 by ktomoya           #+#    #+#             */
/*   Updated: 2023/09/12 14:09:15 by kudoutomoya      ###   ########.fr       */
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
	t_node_tree	*cmd;
	t_node_tree	*child;
	const char	*line;

	(void)argv;
	(void)envp;
	if (argc != 1)
		return (FAILURE);
	while (1)
	{
		line = readline("minishell$ ");
		if (*line)
			add_history(line);
		tokens = lexer(line);
		cmd = parser(tokens);
		
		printf("command: %s, args: ", cmd->first_child->word);
		child = cmd->first_child->next_sibling;
		while (child->next_sibling != NULL)
		{
			printf("%s", child->word);
			printf(", ");
			child = child->next_sibling;
		}
		printf("\n");
		free((void *)line);
	}
	return (0);
}
