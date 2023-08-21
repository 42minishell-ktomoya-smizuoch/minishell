/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:28:37 by ktomoya           #+#    #+#             */
/*   Updated: 2023/08/03 17:21:11 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strtrim(char const *s, char const *set)
{
	char	*trimed;
	size_t	start;
	size_t	end;

	start = 0;
	if (s == NULL || set == NULL)
		return (NULL);
	end = ft_strlen(s);
	while (ft_strchr(set, s[start]) && start < end)
		start++;
	while (start < end && ft_strchr(set, s[end - 1]))
		end--;
	trimed = (char *)ft_calloc(end - start + 1, sizeof(char));
	if (trimed == NULL)
		return (NULL);
	ft_memcpy(trimed, &s[start], end - start);
	return (trimed);
}
