/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_bool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 15:48:20 by ktomoya           #+#    #+#             */
/*   Updated: 2023/09/15 15:10:42 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	startwith(const char *s1, const char *s2)
{
	return (ft_memcmp(s1, s2, ft_strlen(s2)));
}

bool	is_metachar(const char c)
{
	return (c == '|' || c == '&' || c == '<' || c == '>' || c == ' ' || c == '\t');
}

bool	is_blank(const char c)
{
	return (c == ' ' || c == '\t');
}
