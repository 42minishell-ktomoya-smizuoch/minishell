/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 11:30:42 by ktomoya           #+#    #+#             */
/*   Updated: 2023/09/18 19:23:19 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

void	print_node_tree(t_node *node, int depth)
{
	int		i;
	char	word[100];

	if (node == NULL)
		return ;
	i = 0;
	ft_memset(word, 0, 100);
	ft_memcpy(word, node->str, node->len);
	while (i < depth)
	{
		printf("  ");
		i++;
	}
	if (node->kind == NODE_ARGUMENT)
	{
		printf("[%d]command: %s, args: ", depth, word);
		print_argument_list(node->right, depth + 1);
		printf("\n");
	}
	else if (node->kind == NODE_PIPE)
	{
		printf("[%d]pipe\n", depth);
		print_node_tree(node->left, depth + 1);
		print_node_tree(node->right, depth + 1);
	}
	else if (node->kind == NODE_LESS)
	{
		printf("[%d]<, filename: %s\n", depth, word);
		print_node_tree(node->left, depth + 1);
		print_node_tree(node->right, depth + 1);
	}
	else if (node->kind == NODE_GREAT)
	{
		printf("[%d]>, filename: %s\n", depth, word);
		print_node_tree(node->left, depth + 1);
		print_node_tree(node->right, depth + 1);
	}
	else if (node->kind == NODE_DGREAT)
	{
		printf("[%d]>>, filename: %s\n", depth, word);
		print_node_tree(node->left, depth + 1);
		print_node_tree(node->right, depth + 1);
	}
	else if (node->kind == NODE_DLESS)
	{
		print_redirect_list(node, depth);
		printf("\n");
	}
}

//void print_node(t_node *node, int depth) {
//
//	for (int i = 0; i < depth; i++) {
//		printf(" ");
//	}
//
//	if (node->kind == NODE_COMMAND) {
//		printf("[command] %s\n", node->word);
//
//	} else if (node->kind == NODE_ARGUMENT) {
//		printf("[argument] %s\n", node->word);
//
//	} else if (node->kind == NODE_LESS) {
//		printf("[<] %s\n", node->word);
//	} else if (node->kind == NODE_GREAT) {
//		printf("[>] %s\n", node->word);
//	} else if (node->kind == NODE_DGREAT) {
//		printf("[>>] %s\n", node->word);
//	} else if (node->kind == NODE_DLESS) {
//		printf("[<<] %s\n", node->word);
//	}
//
//	if (node->left) {
//		print_node(node->left, depth + 1);
//	}
//
//	if (node->right) {
//		print_node(node->right, depth + 1);
//	}
//}

void	print_argument_list(t_node *node, int depth)
{
	char	word[100];
	if (node == NULL || node->kind == TYPE_EOF)
		return ;

	ft_memset(word, 0, 100);
	ft_memcpy(word, node->str, node->len);
	printf("%s", word);
	if (node->right)
		printf(", ");
	if (node->right && (node->right->kind == NODE_LESS || node->right->kind == NODE_GREAT || node->right->kind == NODE_DLESS || node->right->kind == NODE_DGREAT))
	{
		print_redirect_list(node->right, depth);
	}
	else if (node->right && node->right->kind == NODE_ARGUMENT)
		print_argument_list(node->right, depth + 1);
}

void	print_redirect_list(t_node *node, int depth)
{
	char	word[100];

	if (node == NULL)
		return ;
	ft_memset(word, 0, 100);
	ft_memcpy(word, node->str, node->len);
	if (node->kind == NODE_LESS)
	{
		printf("redirect: <, filename: %s", word);
	}
	else if (node->kind == NODE_GREAT)
	{
		printf("redirect: >, filename: %s", word);
	}
	else if (node->kind == NODE_DGREAT)
	{
		printf("redirect: >>, filename: %s", word);
	}
	else if (node->kind == NODE_DLESS)
	{
		printf("redirect: <<, here_end: %s", word);
	}
	if (node->right)
		printf(", ");
	if (node->right && (node->right->kind == NODE_LESS || node->right->kind == NODE_GREAT || node->right->kind == NODE_DLESS || node->right->kind == NODE_DGREAT))
		print_redirect_list(node->right, depth + 1);
}

void	print_ast(t_node *root)
{
	if (root == NULL)
		return ;
	print_node_tree(root, 0);
}
