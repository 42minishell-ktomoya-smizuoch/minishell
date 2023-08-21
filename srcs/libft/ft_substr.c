/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:55:26 by ktomoya           #+#    #+#             */
/*   Updated: 2023/08/03 17:21:12 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	s_len;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len <= start || len == 0)
		return (ft_calloc(1, sizeof(char)));
	if (s_len - start < len)
		len = s_len - start;
	substr = (char *)ft_calloc(len + 1, sizeof(char));
	if (substr == NULL)
		return (NULL);
	ft_memcpy(substr, &s[start], len);
	return (substr);
}
