/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xmalloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:05:14 by smizuoch          #+#    #+#             */
/*   Updated: 2023/08/31 16:05:49 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_xmalloc(size_t size)
{
	void	*memory;

	memory = malloc(size);
	if (!memory)
	{
		ft_putendl_fd("malloc error", stderr);
		exit(FAILURE);
	}
	return (memory);
}
