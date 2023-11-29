/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 18:48:39 by ktomoya           #+#    #+#             */
/*   Updated: 2023/11/29 15:23:16 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

t_node	*command_line(t_token *tok, int *flag)
{
	t_node	*node;

	node = command(tok, flag);
	if (!node)
		return (NULL);
	if (consume(TYPE_PIPE, tok) && *flag != ERROR)
	{
		if (expect(TYPE_EOF, tok) || expect(TYPE_PIPE, tok))
		{
			*flag = ERROR;
			put_syntax_error(tok->cur);
			return (node);
		}
		node = new_branch(NODE_PIPE, node, command_line(tok, flag));
		if (!node)
		{
			*flag = ERROR;
			return (NULL);
		}
	}
	return (node);
}

t_node	*parser(t_token *token)
{
	t_node	*ast;
	int		flag;

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
