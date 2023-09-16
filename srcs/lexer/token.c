/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:17:52 by ktomoya           #+#    #+#             */
/*   Updated: 2023/09/15 14:12:47 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

void	lstadd_back_token(t_token **lst, t_token *new)
{
	t_token	*last;

	if (!lst || !new)
		set_errno_and_exit("lstadd_back_token: invalid argument\n", EINVAL);
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
}

static enum e_state	update_state(const char c, enum e_state prev)
{
	enum e_state	new;

	new = STATE_GENERAL;
	if (prev == STATE_GENERAL)
	{
		if (c == '\'')
			new = STATE_IN_QUOTE;
		else if (c == '\"')
			new = STATE_IN_DOUBLE_QUOTE;
	}
	else if (prev == STATE_IN_QUOTE)
	{
		if (c == '\'')
			new = STATE_GENERAL;
		else
			new = STATE_IN_QUOTE;
	}
	else if (prev == STATE_IN_DOUBLE_QUOTE)
	{
		if (c == '\"')
			new = STATE_GENERAL;
		else
			new = STATE_IN_DOUBLE_QUOTE;
	}
	return (new);
}

static size_t	get_token_len(const char *s)
{
	size_t	len;
	t_state	state;

	len = 0;
	state = STATE_GENERAL;
	if (s[0] == '\0')
		len = 0;
	else if (startwith(s, ">>") || startwith(s, "<<")
		|| startwith(s, "||"))
		len = 2;
	else if (ft_strchr("><|&", *s) != NULL)
		len = 1;
	else
	{
		while (s[len])
		{
			state = update_state(s[len], state);
			if (is_metachar(s[len]) && state == STATE_GENERAL)
				break ;
			len++;
		}
	}
	return (len);
}

t_token	*new_token(t_type type, const char *p, size_t len)
{
	t_token *token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->str = p;
	token->len = len;
	return (token);
}

t_token	*create_token(const char *str)
{
	t_token	*token;
	size_t 	len;

	if (!str)
		return (NULL);
	len = get_token_len(str);
	if (len == 0)
		token = new_token(TYPE_EOF, str, len);
	else
		token = new_token(TYPE_GENERAL, str, len);
	if (!token)
		return (NULL);
	return (token);
}