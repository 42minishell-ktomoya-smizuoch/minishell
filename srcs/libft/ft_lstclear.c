/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:23:58 by ktomoya           #+#    #+#             */
/*   Updated: 2023/08/03 17:20:52 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*target;

	target = NULL;
	if (lst == NULL || (*del) == NULL)
		return ;
	while (*lst != NULL)
	{
		target = *lst;
		*lst = target->next;
		ft_lstdelone(target, (*del));
	}
}
