/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:50:09 by ktomoya           #+#    #+#             */
/*   Updated: 2023/09/15 13:35:55 by ktomoya          ###   ########.fr       */
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
	char 		*word;
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
		word = ft_substr(cmd->first_child->str, 0, cmd->len);
		printf("command: %s, args: ", word);
		free(word);
		word = NULL;
		child = cmd->first_child;
		while (child->next_sibling)
		{
			child = child->next_sibling;
			word = ft_substr(child->str, 0, child->len);
			printf("%s", word);
			word = NULL;
			free(word);
			if (child->next_sibling)
				printf(", ");
		}
		printf("\n");
		free((void *)line);
	}
	return (0);
}
