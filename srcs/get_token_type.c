/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 15:58:43 by ktomoya           #+#    #+#             */
/*   Updated: 2023/09/03 15:59:18 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

enum e_type	get_token_type(const char *str)
{
	enum e_type	type;

	if (*str == '|')
		type = TYPE_PIPE;
	else if (*str == '&')
		type = TYPE_AMPERSAND;
	else if (*str == '<' || *str == '>')
		type = TYPE_REDIR;
	else if (*str == '\n')
		type = TYPE_NEWLINE;
	else if (*str == '\'')
		type = TYPE_QUOTE;
	else if (*str == '\"')
		type = TYPE_DOUBLE_QUOTE;
	else
		type = TYPE_GENERAL;
	return (type);
}
