/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_space_or_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kudoutomoya <kudoutomoya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 15:48:20 by ktomoya           #+#    #+#             */
/*   Updated: 2023/09/05 16:57:08 by kudoutomoya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_metachar(const char c)
{
	return (c == '|' || c == '&' || c == '<' || c == '>' || c == ' ' || c == '\t');
}

bool	is_space_or_tab(const char c)
{
	return (c == ' ' || c == '\t');
}
