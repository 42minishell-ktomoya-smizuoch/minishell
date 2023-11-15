/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consume.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 05:25:30 by kudoutomoya       #+#    #+#             */
/*   Updated: 2023/11/15 16:18:07 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

//bool	consume(const char *op, t_token *tok)
//{
//	t_token	*cur;
//
//	cur = tok->cur;
//	if (ft_strlen(op) != cur->len || ft_memcmp(cur->str, op, cur->len))
//		return (false);
//	tok->cur = cur->next;
//	return (true);
//}

bool	consume(t_type type, t_token *tok)
{
	t_token	*cur;

	cur = tok->cur;
	if (cur && cur->type != type)
		return (false);
	tok->cur = cur->next;
	return (true);
}

bool	expect(t_type type, t_token *tok)
{
	t_token	*cur;

	cur = tok->cur;
	if (cur && cur->type != type)
		return (false);
	return (true);
}

bool	expect_next(t_type type, t_token *tok)
{
	t_token	*next;

	next = tok->cur->next;
	if (next && next->type != type)
		return (false);
	return (true);
}
