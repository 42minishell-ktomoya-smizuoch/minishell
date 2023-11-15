/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:17:52 by ktomoya           #+#    #+#             */
/*   Updated: 2023/11/15 16:09:30 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

void	lstadd_back_token(t_token **lst, t_token *new)
{
	t_token	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
}

t_token	*new_token(t_type type, const char *p, size_t len)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (perror_null("malloc"));
	token->type = type;
	token->str = p;
	token->len = len;
	token->cur = token;
	return (token);
}

t_token	*create_token(const char *str)
{
	t_token	*token;
	t_type	type;
	ssize_t	len;

	type = get_token_type(str);
	len = get_token_len(str);
	if (len == ERROR)
		return (NULL);
	token = new_token(type, str, len);
	if (!token)
		return (NULL);
	return (token);
}

void	free_token(t_token *token)
{
	if (!token)
		return ;
	free_token(token->next);
	free(token);
}

t_token	*free_token_null(t_token *head)
{
	free_token(head);
	return (NULL);
}
