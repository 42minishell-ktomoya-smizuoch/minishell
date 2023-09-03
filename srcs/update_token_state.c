/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_token_state.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:00:46 by ktomoya           #+#    #+#             */
/*   Updated: 2023/09/03 16:00:52 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

enum e_state	update_token_state(const char *str, enum e_state prev_state)
{
	enum e_state	new_state;

	new_state = STATE_GENERAL;
	if (prev_state == STATE_GENERAL)
	{
		if (*str == '\'')
			new_state = STATE_IN_QUOTE;
		else if (*str == '\"')
			new_state = STATE_IN_DOUBLE_QUOTE;
	}
	else if (prev_state == STATE_IN_QUOTE)
	{
		if (*str == '\'')
			new_state = STATE_GENERAL;
		else
			new_state = STATE_IN_QUOTE;
	}
	else if (prev_state == STATE_IN_DOUBLE_QUOTE)
	{
		if (*str == '\"')
			new_state = STATE_GENERAL;
		else
			new_state = STATE_IN_DOUBLE_QUOTE;
	}
	return (new_state);
}
