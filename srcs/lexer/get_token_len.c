/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kudoutomoya <kudoutomoya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:03:23 by ktomoya           #+#    #+#             */
/*   Updated: 2023/09/05 16:54:39 by kudoutomoya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static size_t	get_general_len(const char *str)
{
	size_t			len;
	enum e_state	state;

	len = 0;
	state = STATE_GENERAL;
	while (str[len])
	{
		state = update_state(str[len], state);
		if (is_metachar(str[len]) && state == STATE_GENERAL)
			break ;
		len++;
	}
	return (len);
}

static size_t	get_redirect_len(const char *str)
{
	size_t	len;

	len = 0;
	if (str[len] == '>')
	{
		len++;
		if (str[len] == '>')
			len++;
	}
	else if (str[len] == '<')
	{
		len++;
		if (str[len] == '<')
			len++;
	}
	return (len);
}

size_t	get_token_len(const char *str)
{
	size_t	len;

	len = 0;
	if (str[len] == '|' || str[len] == '&')
		len++;
	else if (str[len] == '>' || str[len] == '<')
		len = get_redirect_len(str);
	else
		len = get_general_len(str);
	return (len);
}
