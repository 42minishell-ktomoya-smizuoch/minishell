/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fr_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kudoutomoya <kudoutomoya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:19:24 by kudoutomoya       #+#    #+#             */
/*   Updated: 2023/10/12 15:20:18 by kudoutomoya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

size_t	ft_strcspn(const char *s, const char *reject)
{
	const char *p;

	p = s;
	if (reject[0] == '\0' || reject[1] == '\0')
	{
		s = ft_strchrnul(s, *reject);
		return (s - p);
	}
	while (*s != '\0')
	{
		if (ft_strchr(reject, *s))
			break ;
		s++;
	}
	return (s - p);
}
