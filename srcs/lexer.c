/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kudoutomoya <kudoutomoya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:37:58 by ktomoya           #+#    #+#             */
/*   Updated: 2023/09/05 14:39:42 by kudoutomoya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_token	*create_token_list(const char *str)
{
	t_token	*list;
	size_t	token_len;
	t_token	*token;

	list = NULL;
	while (*str)
	{
		skip_spaces(&str);
		if (!*str)
			break ;
		token_len = get_token_len(str);
		if (!token_len)
			continue ;
		token = create_token(str, token_len);
		if (!token)
			set_errno_and_exit("create_token_list: token is NULL\n", ENOMEM);
		lstadd_back_token(&list, token);
		str += token_len;
	}
	return (list);
}

t_token	*lexer(const char *str)
{
	t_token	*token_list;

	if (!str)
		ft_putendl_fd("lexer: str is NULL", STDERR_FILENO);
	token_list = create_token_list(str);
	return (token_list);
}
