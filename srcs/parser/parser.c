/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kudoutomoya <kudoutomoya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 18:48:39 by ktomoya           #+#    #+#             */
/*   Updated: 2023/09/11 16:21:55 by kudoutomoya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// トークン列を受け取り、ASTを返す
// 入力：echo hello
// 出力：command: echo, args: hello
// 作りたいBNF
// <job>       :== <builtin>
// <builtin>   :== echo <argument>
// <argument>  :== <argument> <letter> | <argument> <digit> | <empty>
// <letter>    :== A | B | C | D | E | F | G | H | I | J | K | L | M | N | O | P | Q | R | S | T | U | V | W | X | Y | Z | [ | a | b | c | d | e | f | g | h | i | j | k | l | m | n | o | p | q | r | s | t | u | v | w | x | y | z
// <digit>     :== 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9

void	free_token_list(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current != NULL)
	{
		next = current->next;
		free(current->word);
		free(current);
		current = next;
	}
}

t_ast	*new_node(t_node_kind kind, char *word, t_ast *left, t_ast *right)
{
	t_ast	*node;

	node = ft_calloc(1, sizeof(t_ast));
	if (!node)
		exit(FAILURE);
	node->kind = kind;
	node->data = ft_strdup(word);
	if (!node->data)
		exit(FAILURE);
	node->left = left;
	node->right = right;
	return (node);
}

t_ast	*create_ast(t_token *tokens)
{
	t_ast	*ast;
	t_ast	*left;

	ast = new_node(NODE_COMMAND, tokens->word, NULL, NULL);
	tokens = tokens->next;
	left = new_node(NODE_ARGUMENT, tokens->word, NULL, NULL);
	ast->left = left;
	return (ast);
}

t_ast	*parser(t_token *tokens)
{
	t_ast	*ast;

	if (tokens == NULL)
		return (NULL);
	ast = create_ast(tokens);
	free_token_list(tokens);
	return (ast);
}
