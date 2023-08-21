/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:55:29 by ktomoya           #+#    #+#             */
/*   Updated: 2023/08/03 17:21:08 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	newstr = (char *)ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (newstr == NULL)
		return (NULL);
	ft_memcpy(newstr, s1, ft_strlen(s1));
	ft_memcpy(&newstr[ft_strlen(s1)], s2, ft_strlen(s2));
	return (newstr);
}
