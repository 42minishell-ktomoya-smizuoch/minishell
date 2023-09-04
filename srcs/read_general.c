/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_general.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:13:19 by ktomoya           #+#    #+#             */
/*   Updated: 2023/09/04 19:54:49 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// t_token	*read_general(const char *str)
// {
// 	t_token			*new_token;
// 	enum e_state	state;

// 	new_token = ft_xmalloc(sizeof(t_token));
// 	new_token->type = TYPE_GENERAL;
// 	new_token->len = 0;
// 	while (str[new_token->len] && !is_metachar(str[new_token->len]))
// 		new_token->len++;
// 	new_token->next = NULL;
// 	return (new_token);
// }

t_token	*read_general(const char *str)
{
	t_token			*new_token;
	enum e_state	state;

	new_token = ft_xmalloc(sizeof(t_token));
	new_token->type = TYPE_GENERAL;
	new_token->len = 0;
	state = STATE_GENERAL;
	while (str[new_token->len] && str[new_token->len] != '|' && str[new_token->len] != '&' && str[new_token->len] != '<' && str[new_token->len] != '>')
	{
		if (str[new_token->len] == ' ' && state == STATE_GENERAL)
			break ;
		else if (str[new_token->len] == ' ' && state != STATE_GENERAL)
			new_token->len++;
		else if (str[new_token->len] == '\"' && state == STATE_GENERAL)
		{
			state = STATE_IN_DOUBLE_QUOTE;
			new_token->len++;
		}
		else if (str[new_token->len] == '\"' && state == STATE_IN_DOUBLE_QUOTE)
		{
			state = STATE_GENERAL;
			new_token->len++;
		}
		else if (str[new_token->len] == '\'' && state == STATE_GENERAL)
		{
			state = STATE_IN_QUOTE;
			new_token->len++;
		}
		else if (str[new_token->len] == '\'' && state == STATE_IN_QUOTE)
		{
			state = STATE_GENERAL;
			new_token->len++;
		}
		else
			new_token->len++;
	}
	return (new_token);
}
