/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kudoutomoya <kudoutomoya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:19:39 by ktomoya           #+#    #+#             */
/*   Updated: 2023/09/04 11:27:03 by kudoutomoya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*read_pipe(const char c)
{
	t_token	*new_token;

	if (c != '|')
		set_errno_and_exit("read_pipe: c is not '|'\n", EINVAL);
	new_token = ft_xmalloc(sizeof(t_token));
	new_token->type = TYPE_PIPE;
	new_token->len = ft_strlen("|");
	new_token->next = NULL;
	return (new_token);
}
