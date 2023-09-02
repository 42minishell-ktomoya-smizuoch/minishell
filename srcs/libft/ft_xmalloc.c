/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xmalloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smizuoch <smizuoch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:05:14 by smizuoch          #+#    #+#             */
/*   Updated: 2023/09/02 11:15:47 by smizuoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_xmalloc(size_t size)
{
	void	*memory;

	memory = malloc(size);
	if (!memory)
	{
		ft_putendl_fd("malloc error", STDERR_FILENO);
		exit(FAILURE);
	}
	return (memory);
}
