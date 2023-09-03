/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_double_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:09:41 by ktomoya           #+#    #+#             */
/*   Updated: 2023/09/03 16:21:47 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*read_double_quote(const char **str)
{
	t_token	*new_token;
	size_t	len;

	(*str)++;
	len = 0;
	new_token = ft_xmalloc(sizeof(t_token));
	new_token->type = TYPE_GENERAL;
	while ((*str)[len] && (*str)[len] != '\'')
		len++;
	new_token->word = ft_substr(*str, 0, len);
	new_token->next = NULL;
	(*str) += len;
	return (new_token);
}
