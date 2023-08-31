/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xcalloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smizuoch <smizuoch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:14:49 by smizuoch          #+#    #+#             */
/*   Updated: 2023/08/30 17:16:26 by smizuoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_xcalloc(size_t count, size_t size)
{
	void	*memory;

	if (!(memory == ft_calloc(count, size)))
	{
		ft_putendl_fd("calloc error", 2);
		exit(FAILURE);
	}
	return (memory);	
}
