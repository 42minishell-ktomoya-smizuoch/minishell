/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_ampersand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:24:09 by ktomoya           #+#    #+#             */
/*   Updated: 2023/09/03 16:24:38 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*read_ampersand(const char **str)
{
	t_token	*new_token;

	new_token = ft_xmalloc(sizeof(t_token));
	new_token->type = TYPE_AMPERSAND;
	new_token->word = ft_strdup("&");
	new_token->next = NULL;
	(*str)++;
	return (new_token);
}
