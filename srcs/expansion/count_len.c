/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_len.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:49:16 by ktomoya           #+#    #+#             */
/*   Updated: 2023/11/19 14:26:51 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expansion.h"
#include "../../includes/parser.h"
#include "../../includes/lexer.h"
#include "../../includes/minishell.h"

size_t	count_env_len(const char **key_head, t_env *env)
{
	const char	*key_end = *key_head;
	char		*value;
	size_t		len;

	while (ft_isalnum(*key_end) || *key_end == '_')
		key_end++;
	value = search_nenv(*key_head, env, key_end - *key_head);
	if (value)
		len = ft_strlen(value);
	else
		len = 0;
	*key_head = key_end;
	return (len);
}

size_t	count_digits(int num)
{
	size_t	count;

	count = 1;
	while (num / 10 != 0)
	{
		count++;
		num /= 10;
	}
	return (count);
}

size_t	count_dollsuffix_len(const char **line, t_env *env)
{
	size_t		len;
	const char	*p;

	len = 0;
	p = *line;
	if (ft_isalnum(p[1]) || p[1] == '_')
	{
		p++;
		len += count_env_len(&p, env);
	}
	else if (p[1] == '?')
	{
		p += 2;
		len += count_digits(env->exit_status);
	}
	else
	{
		p++;
		len++;
	}
	*line = p;
	return (len);
}

size_t	count_len(const char *line, t_env *env)
{
	size_t	len;
	t_state	state;

	len = 0;
	state = STATE_GENERAL;
	while (*line)
	{
		state = update_state(*line, state);
		if ((state == STATE_IN_DOUBLE_QUOTE && *line == '$')
			|| (state == STATE_GENERAL && *line == '$' && line[1] != '\0'))
		{
			if (state == STATE_GENERAL && ft_strchr("\'\"", line[1]))
				line++;
			else
				len += count_dollsuffix_len(&line, env);
			continue ;
		}
		else if ((state == STATE_IN_QUOTE && *line != '\'')
			|| (state == STATE_IN_DOUBLE_QUOTE && *line != '\"')
			|| (state == STATE_GENERAL && *line != '\'' && *line != '\"'))
			len++;
		line++;
	}
	return (len);
}
