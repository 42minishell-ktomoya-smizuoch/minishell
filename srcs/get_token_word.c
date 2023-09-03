/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:01:40 by ktomoya           #+#    #+#             */
/*   Updated: 2023/09/03 16:01:58 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_token_word(const char *str, enum e_state prev)
{
	char	*word;
	size_t	len;

	len = 0;
	if (prev == STATE_IN_QUOTE || prev == STATE_IN_DOUBLE_QUOTE)
	{
		// メタ文字以外、ただし、スペースとタブは除くときlen++
		while (str[len] && !is_metachar_except_space(str[len]))
			len++;
	}
	else
	{
		if (is_space_or_tab(*str))
			len++;
		else
		{
			while (str[len] && !is_metachar(str[len]))
				len++;
		}
	}
	word = ft_substr(str, 0, len);
	return (word);
}
