/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 18:48:39 by ktomoya           #+#    #+#             */
/*   Updated: 2023/09/10 20:13:53 by ktomoya          ###   ########.fr       */
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

// void	free_token_list(t_token *tokens)
// {
// 	t_token	*current;
// 	t_token	*next;

// 	current = tokens;
// 	while (current != NULL)
// 	{
// 		next = current->next;
// 		free(current->word);
// 		free(current);
// 		current = next;
// 	}
// }

t_ast	*create_ast(t_token *tokens)
{
	t_ast	*ast;

	ast = ft_calloc(1, sizeof(t_ast));
	if (!ast)
		exit(FAILURE);
	// 現在のトークンのポインタを

}

t_ast	*parser(t_token *tokens)
{
	t_ast	*ast;

	// astにtokensを渡して、astを返す
	if (tokens == NULL)
		return (NULL);
	ast = create_ast(tokens);
	// // tokensをfreeする
	// free_token_list(tokens);
	return (ast);
}
