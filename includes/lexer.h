/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kudoutomoya <kudoutomoya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:56:33 by kudoutomoya       #+#    #+#             */
/*   Updated: 2023/10/14 14:22:16 by kudoutomoya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

typedef enum e_type
{
	TYPE_GENERAL,
	TYPE_PIPE,
	TYPE_AMPERSAND,
	TYPE_REDIRECT,
	TYPE_EOF,
	TYPE_NEWLINE,
}	t_type;

typedef struct s_token
{
	t_type			type;
	struct s_token	*head;
	struct s_token	*cur;
	struct s_token	*next;
	const char		*str;
	size_t			len;
}	t_token;

typedef enum e_state
{
	STATE_GENERAL,
	STATE_IN_QUOTE,
	STATE_IN_DOUBLE_QUOTE
}	t_state;

t_token			*create_token(const char *str);
t_token			*new_token(t_type type, const char *str, size_t len);
size_t			count_token(t_token *tok);
char			**malloc_token(t_token *tok);
size_t			get_token_len(const char *s);
t_type			get_token_type(const char c);
void			lstadd_back_token(t_token **lst, t_token *new);
bool			is_blank(char c);
bool			is_metachar(const char c);
bool			startwith(const char *s1, const char *s2);

#endif
