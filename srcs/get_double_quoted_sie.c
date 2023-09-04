/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_double_quoted_sie.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 19:14:19 by ktomoya           #+#    #+#             */
/*   Updated: 2023/09/04 19:20:54 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	get_double_quoted_len(const char *str)
{
	size_t	len;

	len = 0;
	while (*str)
	{
		if (*str == '\"')
		{
			len++;
			str++;
			while (*str && *str != '\"')
			{
				len++;
				str++;
			}
			if (*str == '\"')
				len++;
		}
		else
		{
			len++;
			str++;
		}
	}
	return (len);
}
