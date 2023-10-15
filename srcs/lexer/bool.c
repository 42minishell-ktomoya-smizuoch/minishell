/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kudoutomoya <kudoutomoya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 15:48:20 by ktomoya           #+#    #+#             */
/*   Updated: 2023/10/14 18:11:27 by kudoutomoya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

bool	startwith(const char *s1, const char *s2)
{
	return (ft_memcmp(s1, s2, ft_strlen(s2)) == 0);
}

bool	is_metachar(const char c)
{
	// return (c == '|' || c == '&' || c == '<' || c == '>' || c == ' ' || c == '\t');
	return (ft_strchr("|&<> \t", c));
}

bool	is_blank(const char c)
{
	return (c == ' ' || c == '\t');
}
