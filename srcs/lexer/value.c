/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kudoutomoya <kudoutomoya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 19:38:37 by kudoutomoya       #+#    #+#             */
/*   Updated: 2023/09/17 19:38:39 by kudoutomoya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

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

size_t	get_token_len(const char *s)
{
	size_t	len;
	t_state	state;

	len = 0;
	state = STATE_GENERAL;
	if (*s == '\0')
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

t_type	get_token_type(const char c)
{
	if (c == '|')
		return (TYPE_PIPE);
	else if (c == '&')
		return (TYPE_AMPERSAND);
	else if (c == '>' || c == '<')
		return (TYPE_REDIRECT);
	else if (c == '\0')
		return (TYPE_EOF);
	else
		return (TYPE_GENERAL);
}
