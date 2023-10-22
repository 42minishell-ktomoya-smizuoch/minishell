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
 * 目標: cmd_suffixの文法を実装する
 * 準目標:
 */

/*
 * リダイレクトの文法
 * コマンド名　引数1 引数2 ... 引数n <リダイレクト1> <リダイレクト2> ... <リダイレクトn>
 */

void	syntax_error(void)
{
	ft_putendl_fd("syntax error", STDERR_FILENO);
	exit(1);
}

/*
 * pipeline = command ('|' command)*
 */
t_node	*pipe_sequence(t_token *tok)
{
	t_node	*node;

	node = command(tok);
	while (1)
	{
		if (consume("|", tok))
			node = new_branch(NODE_PIPE, node, command(tok));
		else
			return (node);
	}
}

/*
 * simple_command ::= cmd_name word_list?
 * word_list ::= word+
 */
//t_node	*command(t_token *tok)
//{
//	t_node	*cmd;
//	t_token	*cur;
//	t_node	*node;
//
//	cmd = NULL;
//	cur = tok->cur;
//	while (cur->type != TYPE_EOF && cur->type != TYPE_PIPE)
//	{
//		node = new_node(NODE_ARGUMENT);
//		if (!node)
//		{
//			// Todo: 構文木をfreeする関数を作る
//			return (NULL);
//		}
//		node->word = ft_substr(cur->str, 0, cur->len);
//		if (node->word == NULL)
//		{
//			// Todo: freeする
//			return (NULL);
//		}
//		lstadd_back_node(&cmd, node);
//		cur = cur->next;
//	}
//	tok->cur = cur;
//	return (cmd);
//}

/* command ::= cmd_name cmd_suffix? */
/* cmd_name ::= WORD */
t_node	*command(t_token *tok)
{
	t_token	*cur;
	t_node	*cmd;
	t_node	*node;

	cur = tok->cur;
	cmd = new_node(NODE_COMMAND);
	node->word = ft_substr(cur->str, 0, cur->len);
	while (1)
	{
		if (cur->type == TYPE_PIPE
			|| cur->type == TYPE_EOF)
			break ;
		else
			node = cmd_suffix
	}
	return (node);
}

/* cmd_suffix ::= (io_redirect | WORD)+ */
t_node	*cmd_suffix(t_token *tok)
{
	t_token	*cur;
	t_node	*node;
	t_node	*suffix;

	node = NULL;
	suffix = NULL;
	while (1)
	{
		cur = tok->cur;
		if (cur->type == TYPE_LESS
			|| cur->type == TYPE_GREAT
			|| cur->type == TYPE_DLESS
			|| cur->type == TYPE_DGREAT)
			node = io_redirect(tok);
		else if (cur->type == TYPE_GENERAL)
		{
			node = new_node(NODE_ARGUMENT);
			node->word = ft_substr(cur->str, 0, cur->len);
			tok->cur = cur->next;
		}
		else
			break ;
		lstadd_back_node(&suffix, node);
	}
	tok->cur = cur->next;
	return (suffix);
}

/* io_redirect ::= io_file | io_here */
t_node	*io_redirect(t_token *tok)
{
	t_node	*node;
	t_token	*cur;

	node = NULL;
	cur = tok->cur;
	if (cur->type == TYPE_LESS
		|| cur->type == TYPE_GREAT
		|| cur->type == TYPE_DGREAT)
		node = io_file(tok);
	else if (cur->type == TYPE_DLESS)
		node = io_here(tok);
	else
		syntax_error();
	return (node);
}

/*
 * io_file ::= ('<' | '>' | '>>') filename
 */
t_node	*io_file(t_token *tok)
{
	t_node	*node;
	t_token	*cur;

	node = NULL;
	cur = tok->cur;
	if (cur->type == TYPE_LESS)
		node = new_node(NODE_LESS);
	else if (cur->type == TYPE_GREAT)
		node = new_node(NODE_GREAT);
	else if (cur->type == TYPE_DGREAT)
		node = new_node(NODE_DGREAT);
	else
		syntax_error();
	cur = cur->next;
	node->word = ft_substr(cur->str, 0, cur->len);
	tok->cur = cur->next;
	return (node);
}

/* '<<' here_end */
t_node	*io_here(t_token *tok)
{
	t_node	*node;
	t_token	*cur;

	node = NULL;
	cur = tok->cur;
	if (cur->type == TYPE_DLESS)
		node = new_node(NODE_DLESS);
	else
		syntax_error();
	cur = cur->next;
	node->word = ft_substr(cur->str, 0, cur->len);
	tok->cur = cur->next;
	return (node);
}
