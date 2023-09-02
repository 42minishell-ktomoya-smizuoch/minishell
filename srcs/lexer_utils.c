/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kudoutomoya <kudoutomoya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:17:52 by ktomoya           #+#    #+#             */
/*   Updated: 2023/09/01 15:49:52 by kudoutomoya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	lstadd_back_token(t_token **lst, t_token *new)
{
	t_token	*last;

	if (!lst || !new)
		set_errno_and_exit("lstadd_back_token: invalid argument\n", EINVAL);
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
}

void	set_errno_and_exit(const char *err_msg, int errno_num)
{
	errno = errno_num;
	ft_putstr_fd(err_msg, STDERR_FILENO);
	exit(FAILURE);
}

enum e_state	update_token_state(const char *str, enum e_state prev_state)
{
	enum e_state	new_state;

	new_state = STATE_GENERAL;
	if (prev_state == STATE_GENERAL)
	{
		if (*str == '\'')
			new_state = STATE_IN_QUOTE;
		else if (*str == '\"')
			new_state = STATE_IN_DOUBLE_QUOTE;
	}
	else if (prev_state == STATE_IN_QUOTE)
	{
		if (*str == '\'')
			new_state = STATE_GENERAL;
		else
			new_state = STATE_IN_QUOTE;
	}
	else if (prev_state == STATE_IN_DOUBLE_QUOTE)
	{
		if (*str == '\"')
			new_state = STATE_GENERAL;
		else
			new_state = STATE_IN_DOUBLE_QUOTE;
	}
	return (new_state);
}

size_t	get_token_len(const char *str, enum e_state current)
{
	size_t	len;

	len = 0;
	if (current == STATE_GENERAL)
	{
		if (is_metachar(str[len]))
			len++;
		else
		{
			while (str[len] && !is_metachar(str[len]))
				len++;
		}
	}
	else if (current == STATE_IN_QUOTE)
	{
		while (str[len] && str[len] != '\'')
			len++;
	}
	else if (current == STATE_IN_DOUBLE_QUOTE)
	{
		while (str[len] && str[len] != '\"')
			len++;
	}
}

t_token	*create_token(const char *str, enum e_state prev_state)
{
	t_token	*new;

	new = (t_token *)ft_xmalloc(sizeof(t_token));
	if (!new)
		set_errno_and_exit("malloc error\n", ENOMEM);
	new->type = get_token_type(str);
	new->word = get_token_word(str, prev_state);
	new->len = ft_strlen(new->word);
	new->state = update_token_state(str, prev_state);
	new->next = NULL;
	return (new);
}
