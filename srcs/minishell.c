/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smizuoch <smizuoch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:50:09 by ktomoya           #+#    #+#             */
/*   Updated: 2023/11/29 15:25:52 by smizuoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	minishell_free(int mode, const char *line, t_env *env, t_node *ast)
{
	if (mode == 0)
	{
		free((void *)line);
		free_env_to_envp(env->envp);
	}
	else if (mode == 1)
	{
		env->exit_status = 258;
		free((void *)line);
		free_env_to_envp(env->envp);
	}
	else if (mode == 2)
	{
		free_node_tree(ast);
		free_env_to_envp(env->envp);
		free((void *)line);
	}
	return (SUCCESS);
}

int	ft_free(void *content)
{
	if (content)
		free(content);
	content = NULL;
	return (SUCCESS);
}

// int	ft_readline(void)
// {
// 	line = readline("minishell$ ");
// 	if (!line && write(1, "exit\n", 5) == 5)
// 		exit(0);
// 	else if (*line)
// 		add_history(line);
// 	else if (*line == '\0' && ft_free((void *)line) == SUCCESS)
// 		continue ;
// }

void	launch_minishell(t_env *env,
		const char	*line, t_token *token, t_node *ast)
{
	while (1)
	{
		set_signal(0);
		check_signal(env);
		line = readline("minishell$ ");
		if (!line && write(1, "exit\n", 5) == 5)
			exit(0);
		else if (*line)
			add_history(line);
		else if (*line == '\0' && ft_free((void *)line) == SUCCESS)
			continue ;
		check_signal(env);
		env->envp = env_to_envp(env);
		token = lexer(line);
		if (!token && minishell_free(0, line, env, NULL) == SUCCESS)
			continue ;
		ast = parser(token);
		if (!ast && minishell_free(1, line, env, NULL) == SUCCESS)
			continue ;
		if (expand(ast, env) == ERROR
			&& minishell_free(2, line, env, ast) == SUCCESS)
			continue ;
		execute(ast, env);
		minishell_free(2, line, env, ast);
	}
}

// execute test
int	main(int argc, char **argv, char **envp)
{
	t_env		env;

	(void)argv;
	if (argc != 1)
		return (FAILURE);
	env.head = NULL;
	env.envp = NULL;
	env.exit_status = 0;
	env.pipe_fd = 0;
	if (env_init(&env, envp) != 0)
		return (FAILURE);
	launch_minishell(&env, NULL, NULL, NULL);
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
