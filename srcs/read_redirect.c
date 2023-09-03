/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:39:17 by ktomoya           #+#    #+#             */
/*   Updated: 2023/09/03 16:53:28 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*read_redirect(const char **str)
{
	t_token	*new_token;
	size_t	len;

	new_token = ft_xmalloc(sizeof(t_token));
	new_token->type = TYPE_REDIRECT;
	len = 0;
	if (*str[0] == '>')
	{
		len++;
		if (*str[1] == '>')
			len++;
	}
	else if (*str[0] == '<')
	{
		len++;
		if (*str[1] == '<')
			len++;
	}
	new_token->word = ft_substr(*str, 0, len);
	new_token->next = NULL;
	(*str) += len;
	return (new_token);
}
