/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 16:43:04 by kudoutomoya       #+#    #+#             */
/*   Updated: 2023/09/18 19:39:04 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	free_token(t_token *token)
{
	if (token->str != NULL)
		free((char *)token->str);
	free(token);
}

void	free_token_list(t_token *head)
{
	t_token	*current;
	t_token	*next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free_token(current);
		current = next;
	}
}

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