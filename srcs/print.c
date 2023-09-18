/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 11:30:42 by ktomoya           #+#    #+#             */
/*   Updated: 2023/09/18 13:43:32 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

void	print_node_tree(t_node *node, int depth)
{
	int	i;

	if (node == NULL)
		return ;
	for (i = 0; i < depth; i++)
		printf("  ");
	if (node->kind == NODE_ARGUMENT)
	{
		printf("command: %s, args: ", node->word);
		free((char *)node->word);
		print_argument_list(node->right, depth + 1);
		printf("\n");
	}
	else if (node->kind == NODE_PIPE)
	{
		printf("pipe: %s\n", node->word);
		print_node_tree(node->left, depth + 1);
		print_node_tree(node->right, depth + 1);
	}
}

void	print_argument_list(t_node *node, int depth)
{
	if (node == NULL)
		return ;
	printf("%s, ", node->word);
	print_argument_list(node->right, depth + 1);
}

void	print_ast(t_node *root)
{
	if (root == NULL)
		return ;
	print_node_tree(root, 0);
}

void	print_pipeline(t_token *tok)
{
	t_node	*root;

	root = pipeline(tok);
	print_ast(root);
	// free_node_tree(root);
}
