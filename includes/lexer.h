/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:56:33 by kudoutomoya       #+#    #+#             */
/*   Updated: 2023/10/27 19:04:58 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"

typedef enum e_type
{
	TYPE_GENERAL,
	TYPE_PIPE,
	TYPE_AMPERSAND,
	TYPE_LESS,
	TYPE_GREAT,
	TYPE_DLESS,
	TYPE_DGREAT,
	TYPE_DOLLAR,
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
ssize_t			get_token_len(const char *s);
t_type			get_token_type(const char *str);
void			lstadd_back_token(t_token **lst, t_token *new);
bool			is_blank(char c);
bool			is_metachar(const char c);
bool			startwith(const char *s1, const char *s2);

void			*perror_null(const char *syscall);

#endif
