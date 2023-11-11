/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smizuoch <smizuoch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:50:09 by ktomoya           #+#    #+#             */
/*   Updated: 2023/11/11 13:07:40 by smizuoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// execute test
int	main(int argc, char **argv, char **envp)
{
	const char	*line;
	t_token		*token;
	t_env		env;
	t_node		*ast;

	(void)argv;
	if (argc != 1)
		return (FAILURE);
	env.head = NULL;
	if (env_init(&env, envp) != 0)
		return (FAILURE);
	while (1)
	{
		g_signal = 0;
		set_signal(0);
		check_signal(&env);
		line = readline("minishell$ ");
		if (!line)
		{
			write(1, "exit\n", 5);
			exit(0);
		}
		else if (*line)
			add_history(line);
		else
			continue ;
		check_signal(&env);
		env.envp = env_to_envp(&env);
		token = lexer(line);
		if (!token)
		{
			free((void *)line);
			continue ;
		}
		ast = parser(token);
		check_signal(&env);
		if (!ast)
		{
			free((void *)line);
			continue ;
		}
		ast = expand(ast, &env);
		execute(ast, &env);
		check_signal(&env);
		free_env_to_envp(env.envp);
		free((void *)line);
	}
	return (0);
}

// parser test
//   int	main(int argc, char **argv, char **envp)
//   {
//   	t_token		*tokens;
//   	t_node		*ast;
//   	const char	*line;

//   	(void)argv;
//   	(void)envp;
//   	if (argc != 1)
//   		return (FAILURE);
//   	while (1)
//   	{
//   		line = readline("minishell$ ");
//   		if (*line)
//   			add_history(line);
//   		tokens = lexer(line);
//   		if (!tokens)
// 		{
// 			free((void *)line);
// 			continue ;
// 		}
//   		ast = parser(tokens);
// 		if (!ast)
// 		{
// 			free((void *)line);
// 			continue ;
// 		}
//   		print_ast(ast);
// 		free_node_tree(ast);
//   		free((void *)line);
//   	}
//   	return (0);
//   }

// lexer test
//int	main(int argc, char **argv)
//{
//	t_token		*token;
//	t_token		*head;
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
//		head = token;
//		while (token)
//		{
//			word = ft_substr(token->str, 0, token->len);
//			printf("type: %d, word: %s\n", token->type, word);
//			free(word);
//			token = token->next;
//		}
//		free((void *)line);
//		free_token(head);
//	}
//	return (0);
//}
