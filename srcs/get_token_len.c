/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:03:23 by ktomoya           #+#    #+#             */
/*   Updated: 2023/09/03 16:04:21 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	get_token_len(const char *str, enum e_state current)
{
	size_t	len;

	len = 0;
	if (current == STATE_GENERAL)
	{
		if (is_metachar(str[len]))
			len++;
		else
		{
			while (str[len] && !is_metachar(str[len]))
				len++;
		}
	}
	else if (current == STATE_IN_QUOTE)
	{
		while (str[len] && str[len] != '\'')
			len++;
	}
	else if (current == STATE_IN_DOUBLE_QUOTE)
	{
		while (str[len] && str[len] != '\"')
			len++;
	}
	return (len);
}
