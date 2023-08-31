/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xcalloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kudoutomoya <kudoutomoya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:14:49 by smizuoch          #+#    #+#             */
/*   Updated: 2023/08/31 12:52:09 by kudoutomoya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_xcalloc(size_t count, size_t size)
{
	void	*memory;

	memory = NULL;
	if (!(memory == ft_calloc(count, size)))
	{
		ft_putendl_fd("calloc error", 2);
		exit(FAILURE);
	}
	return (memory);	
}
