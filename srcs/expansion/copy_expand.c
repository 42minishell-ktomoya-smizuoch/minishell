/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:54:41 by ktomoya           #+#    #+#             */
/*   Updated: 2023/11/17 10:55:03 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expansion.h"
#include "../../includes/parser.h"
#include "../../includes/lexer.h"
#include "../../includes/minishell.h"

void	copy_env(char **dst, const char **src, t_env *env)
{
	const char	*src_nptr;
	char		*dst_nptr;
	const char	*value;

	src_nptr = *src;
	dst_nptr = *dst;
	while (ft_isalnum(*src_nptr) || *src_nptr == '_')
		src_nptr++;
	value = search_nenv(*src, env, src_nptr - *src);
	*src = src_nptr;
	if (!value)
		return ;
	while (*value)
	{
		*dst_nptr = *value;
		dst_nptr++;
		value++;
	}
	*dst = dst_nptr;
}

void	copy_status(char **dst, t_env *env)
{
	char		*dstp;
	size_t		digits;
	size_t		i;
	int			num;

	dstp = *dst;
	digits = count_digits(env->exit_status);
	i = digits;
	num = env->exit_status;
	while (i--)
	{
		dstp[i] = num % 10 + '0';
		num /= 10;
	}
	*dst += digits;
}

void	copy_doll_suffix(char **dst, const char **src, t_env *env)
{
	const char	*srcp;
	char		*dstp;

	srcp = *src;
	dstp = *dst;
	if (ft_isalnum(srcp[1]) || srcp[1] == '_')
	{
		srcp++;
		copy_env(&dstp, &srcp, env);
	}
	else if (srcp[1] == '?')
	{
		srcp += 2;
		copy_status(&dstp, env);
	}
	else
		*dstp++ = *srcp++;
	*dst = dstp;
	*src = srcp;
}

void	copy_expand(char *dst, const char *src, t_env *env)
{
	t_state	state;

	state = STATE_GENERAL;
	while (*src)
	{
		state = update_state(*src, state);
		if ((state == STATE_IN_DOUBLE_QUOTE && *src == '$')
			|| (state == STATE_GENERAL && *src == '$'))
		{
			copy_doll_suffix(&dst, &src, env);
			continue ;
		}
		else if ((state == STATE_IN_QUOTE && *src != '\'')
			|| (state == STATE_IN_DOUBLE_QUOTE && *src != '\"')
			|| (state == STATE_GENERAL && *src != '\'' && *src != '\"'))
			*dst++ = *src;
		src++;
	}
}
