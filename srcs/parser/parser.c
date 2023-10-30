/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 18:48:39 by ktomoya           #+#    #+#             */
/*   Updated: 2023/09/18 19:16:42 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

/* 次の目標: パイプの文法を追加する
 * EBNF
 * pipe = command ('|' command | "||" command)*
 * command = (argument)*
 * argument = word
 *
 * 入力: echo hello | world || ! 
 * 出力: command: echo args: hello
 *		pipe: |
 *		command: world args:
 *      pipe: ||
 * 		command: ! args:
 * 
 * 準目標: 構文木をprintする関数を作る
 * 
 */

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

//t_node	*parser(t_token *token)
//{
//	t_node	*pipeline;
//
//	if (token == NULL)
//		return (NULL);
//	pipeline = command_line(token);
////	free(token);
//	return (pipeline);
//}

t_node	*parser(t_token *token)
{
	t_node	*ast;
	int 	flag;

	flag = 0;
	if (!token)
		return (NULL);
	ast = command_line(token, &flag);
	if (flag == ERROR)
	{
		free_node_tree(ast);
		ast = NULL;
	}
	free_token(token);
	return (ast);
}