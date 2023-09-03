/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_general.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:13:19 by ktomoya           #+#    #+#             */
/*   Updated: 2023/09/03 16:21:35 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*read_general(const char **str)
{
	t_token	*new_token;
	size_t	len;

	len = 0;
	new_token = ft_xmalloc(sizeof(t_token));
	new_token->type = TYPE_GENERAL;
	while ((*str)[len] && !is_metachar((*str)[len]))
		len++;
	new_token->word = ft_substr(*str, 0, len);
	new_token->next = NULL;
	(*str) += len;
	return (new_token);
}