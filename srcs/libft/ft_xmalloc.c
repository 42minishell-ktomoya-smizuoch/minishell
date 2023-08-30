/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xmalloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smizuoch <smizuoch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:05:14 by smizuoch          #+#    #+#             */
/*   Updated: 2023/08/30 17:14:04 by smizuoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_xmalloc(size_t size)
{
	void	*memory;

	if (!(memory == malloc(size)))
	{
		ft_putendl_fd("malloc error", 2);
		exit(FAILURE);
	}
	return (memory);
}
