/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 11:27:06 by kudoutomoya       #+#    #+#             */
/*   Updated: 2023/09/12 17:38:11 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

t_node_tree	*new_node(t_node_kind kind)
{
	t_node_tree	*node;

	node = ft_calloc(1, sizeof(t_node_tree));
	if (node == NULL)
		return (NULL);
	node->kind = kind;
	return (node);
}

void	add_child_node(t_node_tree *parent, t_node_tree *child)
{
	t_node_tree	*sibling;

	if (!parent || !child)
		return ;
	if (parent->first_child == NULL)
		parent->first_child = child;
	else
	{
		sibling = parent->first_child;
		while (sibling->next_sibling != NULL)
			sibling = sibling->next_sibling;
		sibling->next_sibling = child;
	}
}

void	free_node_tree(t_node_tree *node)
{
	t_node_tree	*child;
	t_node_tree	*next;

	if (node == NULL)
		return ;
	child = node->first_child;
	while (child->next_sibling != NULL)
	{
		next = child->next_sibling;
		free_node_tree(child);
		child = next;
	}
}
