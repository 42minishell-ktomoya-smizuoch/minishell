/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kudoutomoya <kudoutomoya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:14:23 by ktomoya           #+#    #+#             */
/*   Updated: 2023/09/12 13:26:17 by kudoutomoya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# include "lexer.h"

t_node	*pipeline(t_token *tokens);
t_node	*command(t_token *tok);
t_node	*new_node(t_node_kind kind);
t_node	*new_branch(t_node_kind kind, t_node *left, t_node *right);
void	add_child_node(t_node *parent, t_node *child);
void	lstadd_back_node(t_node **lst, t_node *new);
bool	consume(const char *op, t_token *tok);
void	free_token(t_token *token);
void	free_token_list(t_token *head);
void	free_node_tree(t_node *node);

#endif