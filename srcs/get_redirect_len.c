/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirect_len.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kudoutomoya <kudoutomoya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 11:38:30 by kudoutomoya       #+#    #+#             */
/*   Updated: 2023/09/05 11:41:42 by kudoutomoya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	get_redirect_len(const char *str)
{
	size_t	len;

	len = 0;
	if (str[len] == '>')
	{
		len++;
		if (str[len] == '>')
			len++;
	}
	else if (str[len] == '<')
	{
		len++;
		if (str[len] == '<')
			len++;
	}
	return (len);
}