/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_bool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 09:39:52 by ktomoya           #+#    #+#             */
/*   Updated: 2023/11/16 10:03:09 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

bool	is_expandable(const char *s, size_t len)
{
	if (ft_memchr(s, '$', len)
		|| ft_memchr(s, '\'', len)
		|| ft_memchr(s, '\"', len))
		return (true);
	return (false);
}
