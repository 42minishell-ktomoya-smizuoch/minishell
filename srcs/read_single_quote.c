/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_single_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 15:56:33 by ktomoya           #+#    #+#             */
/*   Updated: 2023/09/04 14:26:51 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*read_single_quote(const char *str)
{
	t_token	*new_token;

	new_token = ft_xmalloc(sizeof(t_token));
	new_token->type = TYPE_GENERAL;
	new_token->len = ft_strlen("\'");
	while (str[new_token->len] && !is_quoted(str[new_token->len]))
		new_token->len++;
	if (str[new_token->len] == '\'')
		new_token->len++;
	new_token->next = NULL;
	return (new_token);
}