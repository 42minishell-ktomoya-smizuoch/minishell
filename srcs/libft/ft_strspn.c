/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kudoutomoya <kudoutomoya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:14:20 by kudoutomoya       #+#    #+#             */
/*   Updated: 2023/10/12 15:15:38 by kudoutomoya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

size_t  ft_strspn(const char *s, const char *accept)
{
    const char *p;

	if (accept[0] == '\0')
		return (0);
	p = s;
	if (accept[1] == '\0')
	{
		while (*s == *accept)
			s++;
		return (s - p);
	}
    while (*s != '\0')
	{
		if (ft_strchr(accept, *s) == NULL)
			break ;
		s++;
	}
	return (s - p);
}
