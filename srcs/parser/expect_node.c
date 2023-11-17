/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expect_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:11:57 by ktomoya           #+#    #+#             */
/*   Updated: 2023/11/16 10:25:45 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

bool	expect_node(t_node *node, t_node_kind kind)
{
	if (node && node->kind == kind)
		return (true);
	return (false);
}

bool	expect_redirect(t_node *node)
{
	if (expect_node(node, NODE_LESS)
		|| expect_node(node, NODE_GREAT)
		|| expect_node(node, NODE_DGREAT)
		|| expect_node(node, NODE_DLESS))
		return (true);
	return (false);
}

bool	expect_command(t_node *node)
{
	if (expect_node(node, NODE_ARGUMENT)
		|| expect_redirect(node))
		return (true);
	return (false);
}
