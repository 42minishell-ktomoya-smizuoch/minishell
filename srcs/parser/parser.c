/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kudoutomoya <kudoutomoya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 18:48:39 by ktomoya           #+#    #+#             */
/*   Updated: 2023/09/17 17:57:58 by kudoutomoya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

// 次の目標: パイプの文法を追加する
// EBNF
// pipe = command ('|' command | "||" command)*
// command = cmd_name (arg)*
// cmd_name = "echo"
// 入力：echo hello world ! | grep
// 出力：command: echo, args: hello, world, !

// t_node	*new_node(t_node_kind kind, char *word, t_node *left, t_node *right)
// {
// 	t_node	*node;

// 	node = ft_calloc(1, sizeof(t_node));
// 	if (!node)
// 		exit(FAILURE);
// 	node->kind = kind;
// 	node->data = ft_strdup(word);
// 	if (!node->data)
// 		exit(FAILURE);
// 	node->left = left;
// 	node->right = right;
// 	return (node);
// }

// t_node	*create_ast(t_token *tok_lst)
// {
// 	t_node	*ast;
// 	t_node	*node;

// 	// echo
// 	ast = new_node(NODE_COMMAND, tok_lst->str, NULL, NULL);
// 	tok_lst = tok_lst->next;
// 	// hello world !
// 	while (tok_lst->next != NULL)
// 	{
// 		node = new_node(NODE_ARGUMENT, tok_lst->str, NULL, NULL);
// 		// echoのargsにhello, world !を入れる
// 		add_args(ast->args);
// 		tok_lst = tok_lst->next;
// 	}
// 	ast->left = left;
// 	return (ast);
// }

t_node	*parser(t_token *token)
{
	t_node	*simple_command;

	if (token == NULL)
		return (NULL);
	simple_command = command(token);
//	free(tok_lst);
	return (simple_command);
}
