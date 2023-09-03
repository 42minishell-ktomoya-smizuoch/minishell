/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_single_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 15:56:33 by ktomoya           #+#    #+#             */
/*   Updated: 2023/09/03 18:47:16 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*read_single_quote(const char **str)
{
	t_token	*new_token;
	size_t	len;

	len = 1;
	new_token = ft_xmalloc(sizeof(t_token));
	new_token->type = TYPE_GENERAL;
	while ((*str)[len] && (*str)[len] != '\'')
	{
		printf("(*str)[len] = %c\n", (*str)[len]);
		len++;
		printf("len = %zu\n", len);
	}
	new_token->word = ft_substr(*str, 0, len + 1);
	new_token->next = NULL;
	(*str) += len;
	return (new_token);
}
