/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 22:16:56 by kudoutomoya       #+#    #+#             */
/*   Updated: 2023/11/16 08:44:44 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/minishell.h"

/*
 * command ::= cmd_name cmd_suffix?
 *           | cmd_prefix (cmd_word cmd_suffix?)?
 */
t_node	*command(t_token *tok, int *flag)
{
	t_node	*list;
	t_node	*node;

	if (expect(TYPE_PIPE, tok) || expect(TYPE_EOF, tok))
	{
		*flag = ERROR;
		return (syntax_error_null(tok->cur));
	}
	else if (expect(TYPE_GENERAL, tok))
		list = cmd_arg(tok, flag);
	else
		list = io_redirect(tok, flag);
	while (!expect(TYPE_EOF, tok) && !expect(TYPE_PIPE, tok))
	{
		if (expect(TYPE_GENERAL, tok))
			node = cmd_arg(tok, flag);
		else
			node = io_redirect(tok, flag);
		if (!node)
			break ;
		lstadd_back_node(&list, node);
	}
	return (list);
}

/* cmd_arg ::= WORD */
t_node	*cmd_arg(t_token *tok, int *flag)
{
	t_node	*arg;

	if (expect(TYPE_EOF, tok) || *flag == ERROR)
		return (NULL);
	arg = new_node(NODE_ARGUMENT);
	if (!arg)
	{
		*flag = ERROR;
		return (NULL);
	}
	set_node_value(arg, tok->cur->str, tok->cur->len);
	if (consume(TYPE_GENERAL, tok))
		;
	return (arg);
}

/* io_redirect ::= io_file | io_here */
t_node	*io_redirect(t_token *tok, int *flag)
{
	t_node	*node;

	if (expect(TYPE_EOF, tok) || *flag == ERROR)
		return (NULL);
	node = NULL;
	if (expect(TYPE_LESS, tok)
		|| expect(TYPE_GREAT, tok)
		|| expect(TYPE_DGREAT, tok))
		node = io_file(tok, flag);
	else if (consume(TYPE_DLESS, tok))
		node = io_here(tok, flag);
	return (node);
}

/* io_file ::= ('<' | '>' | '>>') filename */
t_node	*io_file(t_token *tok, int *flag)
{
	t_node	*node;

	node = NULL;
	if (consume(TYPE_LESS, tok))
		node = new_node(NODE_LESS);
	else if (consume(TYPE_GREAT, tok))
		node = new_node(NODE_GREAT);
	else if (consume(TYPE_DGREAT, tok))
		node = new_node(NODE_DGREAT);
	if (!node)
	{
		*flag = ERROR;
		return (NULL);
	}
	if (!expect(TYPE_GENERAL, tok))
	{
		*flag = ERROR;
		free(node);
		return (syntax_error_null(tok->cur));
	}
	set_node_value(node, tok->cur->str, tok->cur->len);
	consume(TYPE_GENERAL, tok);
	return (node);
}

/* '<<' here_end */
t_node	*io_here(t_token *tok, int *flag)
{
	t_node	*node;

	node = NULL;
	if (!expect(TYPE_GENERAL, tok))
	{
		*flag = ERROR;
		return (syntax_error_null(tok->cur));
	}
	node = new_node(NODE_DLESS);
	if (!node)
	{
		*flag = ERROR;
		return (NULL);
	}
	set_node_value(node, tok->cur->str, tok->cur->len);
	consume(TYPE_GENERAL, tok);
	return (node);
}
