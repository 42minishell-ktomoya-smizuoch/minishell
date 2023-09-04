/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_single_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kudoutomoya <kudoutomoya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 15:56:33 by ktomoya           #+#    #+#             */
/*   Updated: 2023/09/04 11:39:59 by kudoutomoya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*read_single_quote(const char *str)
{
	t_token	*new_token;

	new_token = ft_xmalloc(sizeof(t_token));
	new_token->type = TYPE_GENERAL;
	new_token->len = 1;
	while (str[new_token->len] && str[new_token->len] != '\'')
	{
		printf("(*str)[len] = %c\n", str[new_token->len]);
		printf("len = %zu\n", new_token->len);
		new_token->len++;
	}
	new_token->next = NULL;
	return (new_token);
}
