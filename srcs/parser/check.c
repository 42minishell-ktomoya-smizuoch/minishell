/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kudoutomoya <kudoutomoya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 05:25:30 by kudoutomoya       #+#    #+#             */
/*   Updated: 2023/09/17 05:25:31 by kudoutomoya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

bool	consume(const char *op, t_token *tok)
{
	if (ft_strlen(op) != tok->len || ft_memcmp(tok->str, op, tok->len))
		return (false);
	tok->cur = tok->next;
	return (true);
}