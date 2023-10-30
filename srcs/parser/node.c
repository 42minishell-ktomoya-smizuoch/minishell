/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 11:27:06 by kudoutomoya       #+#    #+#             */
/*   Updated: 2023/09/18 10:56:23 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

t_node	*new_node(t_node_kind kind)
{
	t_node	*node;

	node = ft_calloc(1, sizeof(t_node));
	if (!node)
		return (perror_null("malloc"));
	node->kind = kind;
	return (node);
}

void	set_node_value(t_node *node, const char *s, size_t len)
{
	node->str = s;
	node->len = len;
}

t_node	*new_branch(t_node_kind kind, t_node *left, t_node *right)
{
	t_node	*node;

	node = new_node(kind);
	if (!node)
	{
		free_node_tree(left);
		free_node_tree(right);
		return (NULL);
	}
	node->left = left;
	node->right = right;
	return (node);
}

//t_node	*new_branch_word(t_node_kind kind, t_token *tok, t_node *left, t_node *right)
//{
//	t_node	*node;
//
//	node = new_node(kind);
//	node->word = ft_substr(tok->str, 0, tok->len);
//	node->left = left;
//	node->right = right;
//	return (node);
//}

//void	add_child_node(t_node *parent, t_node *child)
//{
//	t_node	*sibling;
//
//	if (!parent || !child)
//		return ;
//	if (parent->first_child == NULL)
//		parent->first_child = child;
//	else
//	{
//		sibling = parent->first_child;
//		while (sibling->next_sibling != NULL)
//			sibling = sibling->next_sibling;
//		sibling->next_sibling = child;
//	}
//}

void	lstadd_back_node(t_node **lst, t_node *new)
{
	t_node	*last;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->right)
		last = last->right;
	last->right = new;
}
