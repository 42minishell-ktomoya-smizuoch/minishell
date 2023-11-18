/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consume_right.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 10:29:06 by ktomoya           #+#    #+#             */
/*   Updated: 2023/11/18 10:29:26 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

bool	consume_right(t_node **node, t_node_kind kind)
{
	t_node	*cur;

	cur = *node;
	if (!cur || cur->kind != kind)
		return (false);
	*node = cur->right;
	return (true);
}
