/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 21:03:57 by ktomoya           #+#    #+#             */
/*   Updated: 2023/08/16 17:56:27 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_putstr_fd(const char *s, int fd)
{
	size_t	count;

	count = 0;
	while (s[count])
	{
		if (ft_putchar_fd(s[count], fd) == ERROR)
			return (ERROR);
		count++;
	}
	return (count);
}
