/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 19:38:37 by kudoutomoya       #+#    #+#             */
/*   Updated: 2023/11/15 16:00:32 by ktomoya          ###   ########.fr       */
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

int	puterr_retint(const char *msg)
{
	ft_putendl_fd(msg, STDERR_FILENO);
	return (ERROR);
}

ssize_t	get_token_len(const char *s)
{
	ssize_t	len;
	t_state	state;

	len = 0;
	state = STATE_GENERAL;
	if (startwith(s, ">>") || startwith(s, "<<"))
		len = 2;
	else if (ft_strchr("><|&", *s))
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
		if (state == STATE_IN_QUOTE)
			return (puterr_retint("syntax error: in single quote"));
		else if (state == STATE_IN_DOUBLE_QUOTE)
			return (puterr_retint("syntax error: in double quote"));
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
	else if (*s == '\0')
		return (TYPE_EOF);
	else
		return (TYPE_GENERAL);
}
