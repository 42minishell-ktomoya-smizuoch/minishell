/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_bool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kudoutomoya <kudoutomoya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 15:48:20 by ktomoya           #+#    #+#             */
/*   Updated: 2023/09/05 19:11:36 by kudoutomoya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_metachar(const char c)
{
	return (c == '|' || c == '&' || c == '<' || c == '>' || c == ' ' || c == '\t');
}

bool	is_blank(const char c)
{
	return (c == ' ' || c == '\t');
}
