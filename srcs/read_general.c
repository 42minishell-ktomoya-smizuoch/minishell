/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_general.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kudoutomoya <kudoutomoya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:13:19 by ktomoya           #+#    #+#             */
/*   Updated: 2023/09/04 11:11:51 by kudoutomoya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*read_general(const char *str)
{
	t_token	*new_token;

	new_token = ft_xmalloc(sizeof(t_token));
	new_token->type = TYPE_GENERAL;
	new_token->len = 0;
	while (str[new_token->len] && !is_metachar(str[new_token->len]))
		new_token->len++;
	new_token->next = NULL;
	return (new_token);
}