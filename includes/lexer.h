/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:56:33 by kudoutomoya       #+#    #+#             */
/*   Updated: 2023/09/18 12:02:12 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

typedef enum e_state
{
	STATE_GENERAL,
	STATE_IN_QUOTE,
	STATE_IN_DOUBLE_QUOTE
}	t_state;

t_token			*create_token(const char *str);
t_token			*new_token(t_type type, const char *str, size_t len);
size_t			get_token_len(const char *s);
t_type			get_token_type(const char c);
void			lstadd_back_token(t_token **lst, t_token *new);
bool			is_blank(char c);
bool			is_metachar(const char c);
bool			startwith(const char *s1, const char *s2);

#endif
