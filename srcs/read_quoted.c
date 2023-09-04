/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_quoted.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:29:42 by ktomoya           #+#    #+#             */
/*   Updated: 2023/09/04 13:47:39 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*read_quoted(const char *str)
{
	t_token	*new_token;
	bool	in_quote;

	new_token = ft_xmalloc(sizeof(t_token));
	new_token->type = TYPE_GENERAL;
	in_quote = true;
	new_token->len = 1;
	while (str[new_token->len])
	{
		if (is_quoted(str[new_token->len]))
		{
			if (in_quote && str[new_token->len] == '\'')
				in_quote = false;
			else if (!in_quote && str[new_token->len] == '\'')
				in_quote = true;
			new_token->len++;
		}
		else
			new_token->len++;
	}
	new_token->next = NULL;
	return (new_token);
}