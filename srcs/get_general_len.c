/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_general_len.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kudoutomoya <kudoutomoya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 11:42:37 by kudoutomoya       #+#    #+#             */
/*   Updated: 2023/09/05 12:05:36 by kudoutomoya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	get_general_len(const char *str)
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