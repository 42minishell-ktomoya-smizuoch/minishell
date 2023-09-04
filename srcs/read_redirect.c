/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kudoutomoya <kudoutomoya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:39:17 by ktomoya           #+#    #+#             */
/*   Updated: 2023/09/04 11:20:03 by kudoutomoya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*read_redirect(const char *str)
{
	t_token	*new_token;

	new_token = ft_xmalloc(sizeof(t_token));
	new_token->type = TYPE_REDIRECT;
	new_token->len = 0;
	if (str[0] == '>')
	{
		new_token->len++;
		if (str[1] == '>')
			new_token->len++;
	}
	else if (str[0] == '<')
	{
		new_token->len++;
		if (str[1] == '<')
			new_token->len++;
	}
	new_token->next = NULL;
	return (new_token);
}
