/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kudoutomoya <kudoutomoya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:50:09 by ktomoya           #+#    #+#             */
/*   Updated: 2023/09/17 18:02:00 by kudoutomoya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// parser test
int	main(int argc, char **argv, char **envp)
{
	t_token		*tokens;
	t_node		*arg;
	t_node 		*cur;
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
		arg = parser(tokens);
		if (!arg)
			continue ;
		cur = arg;
		printf("command: %s, args: ", cur->word);
		free((char *)cur->word);
		cur = cur->right;
		while (cur)
		{
			printf("%s", cur->word);
			free((char *)cur->word);
			if (cur->right)
				printf(", ");
			cur = cur->right;
		}
		printf("\n");
		free((void *)line);
	}
	return (0);
}

// lexer test
//int	main(int argc, char **argv)
//{
//	t_token		*token;
//	const char	*line;
//	char 		*word;
//
//	(void)argv;
//	if (argc != 1)
//		return (FAILURE);
//	while (1)
//	{
//		line = readline("minishell$ ");
//		if (*line)
//			add_history(line);
//		token = lexer(line);
//		while (token)
//		{
//			word = ft_substr(token->str, 0, token->len);
//			printf("type: %d, word: %s\n", token->type, word);
//			free(word);
//			token = token->next;
//		}
//		free((void *)line);
//	}
//	return (0);
//}