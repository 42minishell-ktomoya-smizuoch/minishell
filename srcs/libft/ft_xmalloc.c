/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xmalloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kudoutomoya <kudoutomoya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:05:14 by smizuoch          #+#    #+#             */
/*   Updated: 2023/08/31 12:51:44 by kudoutomoya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_xmalloc(size_t size)
{
	void	*memory;

	memory = NULL;
	if (!(memory == malloc(size)))
	{
		ft_putendl_fd("malloc error", 2);
		exit(FAILURE);
	}
	return (memory);
}
