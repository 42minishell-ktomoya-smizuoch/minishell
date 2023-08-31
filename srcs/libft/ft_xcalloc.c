/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xcalloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:14:49 by smizuoch          #+#    #+#             */
/*   Updated: 2023/08/31 16:03:47 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_xcalloc(size_t count, size_t size)
{
	void	*memory;

	memory = ft_calloc(count, size);
	if (!memory)
	{
		ft_putendl_fd("calloc error", stderr);
		exit(FAILURE);
	}
	return (memory);
}
