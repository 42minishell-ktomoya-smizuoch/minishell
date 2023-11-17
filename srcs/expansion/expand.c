/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 09:18:09 by ktomoya           #+#    #+#             */
/*   Updated: 2023/11/17 10:57:22 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expansion.h"
#include "../../includes/parser.h"
#include "../../includes/lexer.h"
#include "../../includes/minishell.h"

t_state	update_state(const char c, t_state prev)
{
	t_state	new;

	new = STATE_GENERAL;
	if (c == '\'')
	{
		if (prev == STATE_GENERAL)
			new = STATE_IN_QUOTE;
		else if (prev == STATE_IN_DOUBLE_QUOTE)
			new = STATE_IN_DOUBLE_QUOTE;
		else if (prev == STATE_IN_QUOTE)
			new = STATE_GENERAL;
	}
	else if (c == '\"')
	{
		if (prev == STATE_GENERAL)
			new = STATE_IN_DOUBLE_QUOTE;
		else if (prev == STATE_IN_QUOTE)
			new = STATE_IN_QUOTE;
		else if (prev == STATE_IN_DOUBLE_QUOTE)
			new = STATE_GENERAL;
	}
	else
		new = prev;
	return (new);
}

char	*expand_node(const char *line, t_env *env)
{
	char	*expanded;
	size_t	len;

	len = count_len(line, env);
	if (len == 0)
		return (NULL);
	expanded = ft_calloc(len + 1, sizeof(char));
	copy_expand(expanded, line, env);
	return (expanded);
}

t_node	*expand(t_node *ast, t_env *env)
{
	char	*unexpand;

	if (!ast)
		return (NULL);
	if (expect_node(ast, NODE_PIPE))
	{
		expand(ast->left, env);
		expand(ast->right, env);
	}
	if (is_expandable(ast->str, ast->len))
	{
		unexpand = ft_substr(ast->str, 0, ast->len);
		if (!unexpand)
			return (perror_null("malloc"));
		ast->expand = expand_node(unexpand, env);
		if (!ast->expand)
			ast->expand_flag = FAILURE;
		free(unexpand);
	}
	else
		ast->expand = NULL;
	expand(ast->right, env);
	return (ast);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	const char	*line;
// 	t_token		*token;
// 	t_node		*ast;
// 	t_env		env;

// 	(void)argv;
// 	if (argc != 1)
// 		return (FAILURE);
// 	env.head = NULL;
// 	if (env_init(&env, envp) != 0)
// 		return (FAILURE);
// 	while (1)
// 	{
// 		line = readline("minishell$ ");
// 		if (!line)
// 		{
// 			write(1, "exit\n", 5);
// 			exit(0);
// 		}
// 		else if (*line)
// 			add_history(line);
// 		else
// 			continue ;
// 		env.envp = env_to_envp(&env);
// 		token = lexer(line);
// 		if (!token)
// 		{
// 			free((void *)line);
// 			free_env_to_envp(env.envp);
// 			continue ;
// 		}
// 		ast = parser(token);
// 		if (!ast)
// 		{
// 			free((void *)line);
// 			free_env_to_envp(env.envp);
// 			continue ;
// 		}
// 		ast = expand(ast, &env);
// 		print_ast(ast);
// 		free_node_tree(ast);
// 		free_env_to_envp(env.envp);
// 		free((void *)line);
// 	}
// 	return (0);
// }
