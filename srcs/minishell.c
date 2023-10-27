/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:50:09 by ktomoya           #+#    #+#             */
/*   Updated: 2023/10/27 19:22:08 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// execute test
//int	main(int argc, char **argv, char **envp)
//{
//	t_token		*tokens;
//	t_node		*ast;
//	const char	*line;
//
//	(void)argv;
//	(void)envp;
//	if (argc != 1)
//		return (FAILURE);
//	while (1)
//	{
//		line = readline("minishell$ ");
//		if (*line)
//			add_history(line);
//		else
//			continue ;
//		tokens = lexer(line);
//		ast = parser(tokens);
//		print_ast(ast);
//		free((void *)line);
//	}
//	return (0);
//}

// parser test
//  int	main(int argc, char **argv, char **envp)
//  {
//  	t_token		*tokens;
//  	t_node		*ast;
//  	const char	*line;

//  	(void)argv;
//  	(void)envp;
//  	if (argc != 1)
//  		return (FAILURE);
//  	while (1)
//  	{
//  		line = readline("minishell$ ");
//  		if (*line)
//  			add_history(line);
//  		tokens = lexer(line);
//  		if (!tokens)
//  			continue ;
//  		ast = parser(tokens);
//  		print_ast(ast);
//  		free((void *)line);
//  	}
//  	return (0);
//  }

// lexer test
int	main(int argc, char **argv)
{
	t_token		*token;
	const char	*line;
	char 		*word;

	(void)argv;
	if (argc != 1)
		return (FAILURE);
	while (1)
	{
		line = readline("minishell$ ");
		if (*line)
			add_history(line);
		token = lexer(line);
		while (token)
		{
			word = ft_substr(token->str, 0, token->len);
			printf("type: %d, word: %s\n", token->type, word);
			free(word);
			token = token->next;
		}
		free((void *)line);
	}
	return (0);
}
