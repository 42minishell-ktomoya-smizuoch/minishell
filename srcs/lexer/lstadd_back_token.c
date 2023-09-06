/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstadd_back_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kudoutomoya <kudoutomoya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:05:17 by ktomoya           #+#    #+#             */
/*   Updated: 2023/09/05 14:59:04 by kudoutomoya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	lstadd_back_token(t_token **lst, t_token *new)
{
	t_token	*last;

	if (!lst || !new)
		set_errno_and_exit("lstadd_back_token: invalid argument\n", EINVAL);
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
