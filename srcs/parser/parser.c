/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kudoutomoya <kudoutomoya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 18:48:39 by ktomoya           #+#    #+#             */
/*   Updated: 2023/09/14 18:14:36 by kudoutomoya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

// 次の目標: argsを複数入れられるようにする
// 入力：echo hello world !
// 出力：command: echo, args: hello, world, !
// 作りたいBNF
// simple_command: cmd_name cmd_suffix
// cmd_name: word
// cmd_suffix: word
// 			 | cmd_suffix word

void	free_token(t_token *token)
{
	if (token->str != NULL)
		free(token->str);
	free(token);
}

void	free_token_list(t_token *tok_lst)
{
	t_token	*current;
	t_token	*next;

	current = tok_lst;
	while (current != NULL)
	{
		next = current->next;
		free_token(current);
		current = next;
	}
}

// t_node_tree	*new_node(t_node_kind kind, char *word, t_node_tree *left, t_node_tree *right)
// {
// 	t_node_tree	*node;

// 	node = ft_calloc(1, sizeof(t_node_tree));
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

// t_node_tree	*create_ast(t_token *tok_lst)
// {
// 	t_node_tree	*ast;
// 	t_node_tree	*node;

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

t_node_tree	*parse_simple_command(t_token *tok_lst)
{
	t_node_tree	*cmd;
	t_node_tree	*arg;
	t_token		*token;

	if (tok_lst == NULL)
		return (NULL);
	cmd = new_node(NODE_COMMAND);
	if (cmd == NULL)
	{
		free_token_list(tok_lst);
		return (NULL);
	}
	token = tok_lst;
	while (token)
	{
		arg = new_node(NODE_ARGUMENT);
		if (arg == NULL)
		{
			free_node_tree(cmd);
			free_token_list(tok_lst);
			return (NULL);
		}
		arg->word = ft_strdup(token->str);
		if (arg->word == NULL)
		{
			free_node_tree(cmd);
			free_token_list(tok_lst);
			free(arg);
			return (NULL);
		}
		add_child_node(cmd, arg);
		token = token->next;
	}
	return (cmd);
}

t_node_tree	*parser(t_token *tok_lst)
{
	t_node_tree	*simple_command;

	if (tok_lst == NULL)
		return (NULL);
	simple_command = parse_simple_command(tok_lst);
	free_token_list(tok_lst);
	return (simple_command);
}
