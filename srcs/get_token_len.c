/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kudoutomoya <kudoutomoya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:03:23 by ktomoya           #+#    #+#             */
/*   Updated: 2023/09/05 14:42:01 by kudoutomoya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static size_t	get_general_len(const char *str)
{
	size_t			len;
	enum e_state	state;

	len = 0;
	state = STATE_GENERAL;
	while (str[len] && str[len] != '|' && str[len] != '&' && str[len] != '<' && str[len] != '>')
	{
		state = update_state(str[len], state);
		if (str[len] == ' ' && state == STATE_GENERAL)
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
