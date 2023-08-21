/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 19:16:00 by ktomoya           #+#    #+#             */
/*   Updated: 2023/08/03 17:21:09 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*cast_s;
	unsigned int	len;

	if (s == NULL || (*f) == NULL)
		return (NULL);
	len = ft_strlen(s);
	cast_s = (char *)ft_calloc(len + 1, sizeof(char));
	if (cast_s == NULL)
		return (NULL);
	while (len--)
		cast_s[len] = (*f)(len, s[len]);
	return (cast_s);
}
