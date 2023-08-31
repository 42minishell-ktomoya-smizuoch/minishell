/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kudoutomoya <kudoutomoya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:17:52 by ktomoya           #+#    #+#             */
/*   Updated: 2023/08/31 14:19:33 by kudoutomoya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	lstadd_back_token(t_token_list **lst, t_token *new)
{
	t_token_list	*last;

	if (!lst || !new)
		set_errno_and_exit("lstadd_back_token: invalid argument\n", EINVAL);
	if (!*lst)
	{
		(*lst)->token = new;
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
}

t_token *create_token(const char *str)
{
	t_token *new;

	new = (t_token *)ft_xmalloc(sizeof(t_token));
	if (!new)
		set_errno_and_exit("malloc error\n", ENOMEM);
	new->type = get_token_type(str);
	new->word = get_word(str);
	new->len = ft_strlen(new->word);
	new->state = STATE_GENERAL;
	return (new);
}
