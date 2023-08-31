/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:17:52 by ktomoya           #+#    #+#             */
/*   Updated: 2023/08/31 17:31:15 by ktomoya          ###   ########.fr       */
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

enum e_state	get_token_state(const char *str)
{
	enum e_state	state;

	if (*str == '\'')
		state = STATE_IN_QUOTE;
	else if (*str == '\"')
		state = STATE_IN_DOUBLE_QUOTE;
	else
		state = STATE_GENERAL;
	return (state);
}

t_token *create_token(const char *str)
{
	t_token *new;

	new = (t_token *)ft_xmalloc(sizeof(t_token));
	if (!new)
		set_errno_and_exit("malloc error\n", ENOMEM);
	new->type = get_token_type(str);
	new->word = get_token_word(str);
	new->len = ft_strlen(new->word);
	new->state = get_token_state(str);
	new->next = NULL;
	return (new);
}
