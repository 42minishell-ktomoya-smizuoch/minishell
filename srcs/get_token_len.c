/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kudoutomoya <kudoutomoya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:03:23 by ktomoya           #+#    #+#             */
/*   Updated: 2023/09/05 13:27:49 by kudoutomoya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	get_token_len(const char *str)
{
	size_t	len;

	len = 0;
	if (str[len] == '|' || str[len] == '&')
		len++;
	else if (str[len] == '>' || str[len] == '<')
		len = get_redirect_len(str);
	else
		len = get_general_len(str);
	return (len);
}
