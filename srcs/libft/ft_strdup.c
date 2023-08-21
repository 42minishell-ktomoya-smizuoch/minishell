/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:56:46 by ktomoya           #+#    #+#             */
/*   Updated: 2023/08/03 17:21:03 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strdup(const char *src)
{
	char	*dest;

	dest = (char *)ft_calloc(ft_strlen(src) + 1, sizeof(char));
	if (dest == NULL)
	{
		errno = ENOMEM;
		return (NULL);
	}
	ft_memcpy(dest, src, ft_strlen(src));
	return (dest);
}
