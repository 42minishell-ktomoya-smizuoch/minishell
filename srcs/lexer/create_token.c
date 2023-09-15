/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:17:52 by ktomoya           #+#    #+#             */
/*   Updated: 2023/09/15 14:12:47 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static enum e_type	get_token_type(const char *str)
{
	enum e_type	type;

	if (*str == '|')
		type = TYPE_PIPE;
	else if (*str == '&')
		type = TYPE_AMPERSAND;
	else if (*str == '<' || *str == '>')
		type = TYPE_REDIRECT;
	else
		type = TYPE_GENERAL;
	return (type);
}

// t_token	*create_token(const char *str, size_t token_len)
// {
// 	t_token	*new;

// 	if (!token_len)
// 		return (NULL);
// 	new = (t_token *)malloc(sizeof(t_token));
// 	if (!new)
// 		set_errno_and_exit("malloc error\n", ENOMEM);
// 	new->type = get_token_type(str);
// 	new->str = ft_substr(str, 0, token_len);
// 	new->next = NULL;
// 	return (new);
// }

t_token	*create_token(const char *str)
{
	t_token	*token;
	size_t	len;

	if (*str == NULL)
		return (NULL);
	len = get_token_len(str);
	return (token);
}