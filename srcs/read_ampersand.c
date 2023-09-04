/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_ampersand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kudoutomoya <kudoutomoya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:24:09 by ktomoya           #+#    #+#             */
/*   Updated: 2023/09/04 11:38:55 by kudoutomoya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*read_ampersand(const char c)
{
	t_token	*new_token;

	if (c != '&')
		set_errno_and_exit("read_ampersand: c is not '&'\n", EINVAL);
	new_token = ft_xmalloc(sizeof(t_token));
	new_token->type = TYPE_AMPERSAND;
	new_token->len = ft_strlen("&");
	new_token->next = NULL;
	return (new_token);
}
