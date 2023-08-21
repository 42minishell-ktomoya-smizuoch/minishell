/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:15:48 by ktomoya           #+#    #+#             */
/*   Updated: 2023/08/03 17:21:10 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*big_ptr;
	size_t	i;
	size_t	j;

	i = 0;
	big_ptr = (char *)big;
	if (little[0] == '\0')
		return (big_ptr);
	if (len == 0)
		return (NULL);
	while (big_ptr[i] != '\0' && i < len)
	{
		j = 0;
		while (little[j] != '\0' && i + j < len)
		{
			if (big_ptr[i + j] != little[j])
				break ;
			j++;
		}
		if (little[j] == '\0')
			return (&big_ptr[i]);
		i++;
	}
	return (NULL);
}
