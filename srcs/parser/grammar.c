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
 * 目標: 木構造から単純なコマンドを実行できるようにする
 * 準目標: commandの構造体を作って、nodeに追加する
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
 * command = argument (argument)*
 * argument = word
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
