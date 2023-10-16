/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 22:16:56 by kudoutomoya       #+#    #+#             */
/*   Updated: 2023/09/18 19:17:25 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

/*
 * 目標: リダイレクトの文法を実装する
 * 準目標: bnf記法を理解する
 */

/*
 * リダイレクトの文法
 * コマンド名　引数1 引数2 ... 引数n <リダイレクト1> <リダイレクト2> ... <リダイレクトn>
 */

/*
 * pipeline = command ('|' command | "||" command)*
 */
t_node	*pipeline(t_token *tok)
{
	t_node	*node;

	node = command(tok);
	while (1)
	{
		if (consume("||", tok))
			node = new_branch(NODE_PIPE, node, command(tok));
		else if (consume("|", tok))
			node = new_branch(NODE_PIPE, node, command(tok));
		else
			return (node);
	}
}

/*
 * simple_command ::= cmd_name word_list?
 * word_list ::= word+
 */
t_node	*command(t_token *tok)
{
	t_node	*cmd;
	t_token	*cur;
	t_node	*node;

	cmd = NULL;
	cur = tok->cur;
	while (cur->type != TYPE_EOF && cur->type != TYPE_PIPE)
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
