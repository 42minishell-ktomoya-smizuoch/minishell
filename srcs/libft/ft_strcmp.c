/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smizuoch <smizuoch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 17:41:41 by smizuoch          #+#    #+#             */
/*   Updated: 2023/09/02 17:47:39 by smizuoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int				dif;
	unsigned char	*ls1;
	unsigned char	*ls2;

	if (!s1 || !s2)
		return (FAILURE);
	dif = 0;
	ls1 = (unsigned char *)s1;
	ls2 = (unsigned char *)s2;
	while (1)
	{
		dif = *ls1 - *ls2;
		if (dif != 0)
			return (dif);
		if (*ls1 == '\0')
			break ;
		ls1++;
		ls2++;
	}
	return (SUCCESS);
}
