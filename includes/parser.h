/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:14:23 by ktomoya           #+#    #+#             */
/*   Updated: 2023/11/18 10:30:07 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include "lexer.h"

typedef enum e_node_kind
{
	NODE_ARGUMENT,
	NODE_PIPE,
	NODE_LESS,
	NODE_GREAT,
	NODE_DLESS,
	NODE_DGREAT,
}	t_node_kind;

typedef struct s_node
{
	t_node_kind		kind;
	struct s_node	*left;
	struct s_node	*right;
	const char		*str;
	size_t			len;
	char			*expand;
	int				expand_flag;
}	t_node;

// nodeの構造体にcomanndの構造体を追加する
// comanndの構造体にはargumentとリダイレクトの構造体を追加する
// argumentとリダイレクト

t_node	*command_line(t_token *tokens, int *flag);
t_node	*cmd_suffix(t_token *tok);
t_node	*io_file(t_token *tok, int *flag);
t_node	*io_here(t_token *tok, int *flag);
t_node	*io_redirect(t_token *tok, int *flag);
t_node	*command(t_token *tok, int *flag);
t_node	*cmd_arg(t_token *tok, int *flag);
t_node	*new_node(t_node_kind kind);
void	set_node_value(t_node *node, const char *s, size_t len);
t_node	*new_branch(t_node_kind kind, t_node *left, t_node *right);
void	add_child_node(t_node *parent, t_node *child);
void	lstadd_back_node(t_node **lst, t_node *new);
bool	consume(t_type type, t_token *tok);
bool	expect(t_type type, t_token *tok);
bool	expect_next(t_type type, t_token *tok);
bool	expect_node(t_node *node, t_node_kind kind);
bool	expect_redirect(t_node *node);
bool	expect_command(t_node *node);
bool	consume_type(t_type type, t_token *tok);
bool	consume_right(t_node **node, t_node_kind kind);
void	free_token(t_token *tok);
void	free_token_list(t_token *head);
void	free_node_tree(t_node *node);
void	put_syntax_error(t_token *tok);
void	*syntax_error_null(t_token *tok);

#endif