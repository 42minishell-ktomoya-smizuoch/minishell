/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smizuoch <smizuoch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:48:07 by ktomoya           #+#    #+#             */
/*   Updated: 2023/10/04 15:09:29 by smizuoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int				dif;
	unsigned char	*ls1;
	unsigned char	*ls2;

	if (s1 == NULL || s2 == NULL)
		return (1);
	dif = 0;
	ls1 = (unsigned char *)s1;
	ls2 = (unsigned char *)s2;
	while (n--)
	{
		dif = *ls1 - *ls2;
		if (dif != 0)
			return (dif);
		if (*ls1 == '\0')
			break ;
		ls1++;
		ls2++;
	}
	return (0);
}
