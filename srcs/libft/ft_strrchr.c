/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:25:53 by ktomoya           #+#    #+#             */
/*   Updated: 2023/08/03 17:21:11 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*s_ptr;
	size_t	len;

	s_ptr = (char *)s;
	len = ft_strlen(s);
	while (len + 1 > 0)
	{
		if (s_ptr[len] == (char)c)
			return (&s_ptr[len]);
		len--;
	}
	if (s_ptr[len] == '\0' && (char)c == '\0')
		return (&s_ptr[len]);
	return (NULL);
}
