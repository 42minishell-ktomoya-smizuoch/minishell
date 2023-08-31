/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:17:52 by ktomoya           #+#    #+#             */
/*   Updated: 2023/08/31 18:13:46 by ktomoya          ###   ########.fr       */
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

// enum e_state	get_token_state(const char *str)
// {
// 	enum e_state	state;

// 	if (*str == '\'')
// 		state = STATE_IN_QUOTE;
// 	else if (*str == '\"')
// 		state = STATE_IN_DOUBLE_QUOTE;
// 	else
// 		state = STATE_GENERAL;
// 	return (state);
// }

// enum e_state	update_token_state(const char *str, enum e_state state)
// {
// 	enum e_state	new_state;

// 	if (*str == '\'')
// 		new_state = STATE_IN_QUOTE;
// 	else if (*str == '\"')
// 		new_state = STATE_IN_DOUBLE_QUOTE;
// 	else
// 		new_state = STATE_GENERAL;
// 	return (new_state);
// }

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

t_token *create_token(const char *str, enum e_state prev_state)
{
	t_token *new;

	new = (t_token *)ft_xmalloc(sizeof(t_token));
	if (!new)
		set_errno_and_exit("malloc error\n", ENOMEM);
	new->type = get_token_type(str);
	new->word = get_token_word(str);
	new->len = ft_strlen(new->word);
	new->state = update_token_state(str, prev_state);
	new->next = NULL;
	return (new);
}
