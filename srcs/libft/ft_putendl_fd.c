/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 20:47:53 by ktomoya           #+#    #+#             */
/*   Updated: 2023/08/03 17:20:59 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_putendl_fd(const char *s, int fd)
{
	int	len;

	len = ft_putstr_fd(s, fd);
	if (len == ERROR)
		return (ERROR);
	len += (int)write(fd, "\n", 1);
	if (len != (int)ft_strlen(s) + 1)
		return (ERROR);
	return (len);
}
