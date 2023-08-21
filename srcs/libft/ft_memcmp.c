/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 19:26:31 by ktomoya           #+#    #+#             */
/*   Updated: 2023/08/03 17:20:56 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int				dif;
	unsigned char	*s1_ptr;
	unsigned char	*s2_ptr;

	dif = 0;
	s1_ptr = (unsigned char *)s1;
	s2_ptr = (unsigned char *)s2;
	while (n--)
	{
		dif = *s1_ptr - *s2_ptr;
		if (dif != 0)
			return (dif);
		s1_ptr++;
		s2_ptr++;
	}
	return (0);
}
