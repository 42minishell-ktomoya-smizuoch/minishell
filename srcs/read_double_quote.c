/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_double_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:09:41 by ktomoya           #+#    #+#             */
/*   Updated: 2023/09/04 12:00:11 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*read_double_quote(const char *str)
{
	t_token	*new_token;

	new_token = ft_xmalloc(sizeof(t_token));
	new_token->type = TYPE_GENERAL;
	new_token->len = ft_strlen("\"");
	while (str[new_token->len] && str[new_token->len] != '\"')
		new_token->len++;
	if (str[new_token->len] == '\"')
		new_token->len++;
	new_token->next = NULL;
	return (new_token);
}
