/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 09:18:09 by ktomoya           #+#    #+#             */
/*   Updated: 2023/11/21 12:27:46 by ktomoya          ###   ########.fr       */
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

int	expand_node(t_node *node, t_env *env)
{
	char	*unexpand;
	size_t	len;

	unexpand = ft_substr(node->str, 0, node->len);
	if (!unexpand)
		return (ERROR);
	len = count_len(unexpand, env);
	if (len == 0)
	{
		node->expand_flag = FAILURE;
		return (FAILURE);
	}
	node->expand = ft_calloc(len + 1, sizeof(char));
	if (!node->expand)
	{
		free(unexpand);
		return (ERROR);
	}
	copy_expand(node->expand, unexpand, env);
	free(unexpand);
	return (SUCCESS);
}

int	expand(t_node *ast, t_env *env)
{
	if (!ast)
		return (FAILURE);
	if (expect_node(ast, NODE_PIPE))
	{
		if (expand(ast->left, env) == ERROR)
			return (ERROR);
		if (expand(ast->right, env) == ERROR)
			return (ERROR);
		return (SUCCESS);
	}
	if (is_expandable(ast->str, ast->len))
	{
		if (expand_node(ast, env) == ERROR)
			return (perror_retint("malloc", ERROR));
	}
	else
		ast->expand = NULL;
	return (expand(ast->right, env));
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
