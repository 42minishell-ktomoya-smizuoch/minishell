/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 19:38:37 by kudoutomoya       #+#    #+#             */
/*   Updated: 2023/10/27 19:21:04 by ktomoya          ###   ########.fr       */
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
	else if (*s == '$')
	{
		// 英数字が続く間、lenを増やす
		len++;
		while (1)
		{
			if (s[len] == '?')
			{
				len++;
				break ;
			}
			else if (ft_isalnum(s[len]))
				len++;
			else
				break ;
		}
	}
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

t_type	get_token_type(const char *s)
{
	if (*s == '|')
		return (TYPE_PIPE);
	else if (*s == '&')
		return (TYPE_AMPERSAND);
	else if (ft_strncmp(s, ">>", 2) == 0)
		return (TYPE_DGREAT);
	else if (ft_strncmp(s, "<<", 2) == 0)
		return (TYPE_DLESS);
	if (*s == '>')
		return (TYPE_GREAT);
	else if (*s == '<')
		return (TYPE_LESS);
	else if (*s == '$')
		return (TYPE_DOLLAR);
	else if (*s == '\0')
		return (TYPE_EOF);
	else
		return (TYPE_GENERAL);
}
