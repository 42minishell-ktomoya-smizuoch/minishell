/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kudoutomoya <kudoutomoya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 22:16:56 by kudoutomoya       #+#    #+#             */
/*   Updated: 2023/09/17 18:04:24 by kudoutomoya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

/* 次の目標: パイプの文法を追加する
 * EBNF
 * pipe = command ('|' command | "||" command)*
 * command = (argument)*
 * argument = word
 */

/*
 * 準目標: tokenの構造体にトークンの消費位置を示すポインタcurを追加する
 * 準目標: tokenのタイプを追加する
 * 準目標: consume関数を作り直す→問題なし
 * 準目標: new_node関数を作り直す
 */

/*
 * pipeline = command ('|' command | "||" command)*
 */
t_node	*pipeline(t_token *tok)
{
	t_node *node;

	node = command(tok->cur);
	while (1)
	{
		if (consume("||", tok->cur))
			node = new_node(NODE_PIPE, node, command(tok));
		else if (consume("|", tok->cur))
			node = new_node(NODE_PIPE, node, command(tok));
		else
			return (node);
	}
}

/* command = cmd_name (arg)* */
//t_node	*command(t_token *tok_lst)
//{
//	t_node	*cmd;
//	t_node	*arg;
//	t_token		*token;
//
//	if (tok_lst == NULL)
//		return (NULL);
//	cmd = new_node(NODE_COMMAND, tok_lst->str, tok_lst->len);
//	if (cmd == NULL)
//	{
//		free(tok_lst);
//		return (NULL);
//	}
//	token = tok_lst;
//	while (token->type != TYPE_EOF)
//	{
//		arg = new_node(NODE_ARGUMENT, token->str, token->len);
//		if (arg == NULL)
//		{
//			free_node_tree(cmd);
//			free(tok_lst);
//			return (NULL);
//		}
//		add_child_node(cmd, arg);
//		token = token->next;
//	}
//	tok_lst->cur = token;
//	return (cmd);
//}

/* command = argument (argument)*
 * argument = word
 */
t_node *command(t_token *tok)
{
	t_node 	*cmd;
	t_token	*cur;
	t_node 	*node;

	cmd = NULL;
	cur = tok;
	while (cur->type != TYPE_EOF)
	{
		node = new_node(NODE_ARGUMENT);
		if (!node)
		{
			// Todo: 構文木をfreeする関数を作る
			return (NULL);
		}
		node->word = ft_substr(cur->str, 0, cur->len);
		if (node->word == NULL)
		{
			// Todo: freeする
			return (NULL);
		}
		lstadd_back_node(&cmd, node);
		cur = cur->next;
	}
	tok->cur = cur;
	return (cmd);
}

