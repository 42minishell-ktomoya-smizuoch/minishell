/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 16:43:04 by kudoutomoya       #+#    #+#             */
/*   Updated: 2023/11/15 07:38:20 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

//void	free_node_tree(t_node *node)
//{
//	t_node	*child;
//	t_node	*next;
//
//	if (node == NULL)
//		return ;
//	child = node->first_child;
//	while (child->next_sibling != NULL)
//	{
//		next = child->next_sibling;
//		free_node_tree(child);
//		child = next;
//	}
//}

void	free_node_tree(t_node *node)
{
	if (!node)
		return ;
	if (node->left)
		free_node_tree(node->left);
	if (node->right)
		free_node_tree(node->right);
	if (node->expand)
		free(node->expand);
	free(node);
	node = NULL;
}

void	free_node_list(t_node *head)
{
	t_node	*current;
	t_node	*next;

	current = head;
	while (current)
	{
		next = current->right;
		free(current);
		current = next;
	}
}
