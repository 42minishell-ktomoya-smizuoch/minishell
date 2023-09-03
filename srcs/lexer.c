/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:37:58 by ktomoya           #+#    #+#             */
/*   Updated: 2023/09/03 16:52:54 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// t_token	*tokenize(const char *str)
// {
// 	t_token	*new_token;
// 	t_token	*head;

// 	if (!str)
// 		set_errno_and_exit("tokenize: str is NULL\n", EINVAL);
// 	head = NULL;
// 	while (*str)
// 	{
// 		skip_spaces(&str, new_token->state);
// 		new_token = create_token(str, new_token->state);
// 		lstadd_back_token(&head, new_token);
// 		str += new_token->len;
// 	}
// 	return (head);
// }

// t_token	*tokenize(const char *str)
// {
// 	t_token			*new_token;
// 	t_token			*lst;
// 	enum e_state	current_state;

// 	if (!str)
// 		set_errno_and_exit("tokenize: str is NULL\n", EINVAL);
// 	lst = NULL;
// 	current_state = STATE_GENERAL;
// 	while (*str)
// 	{
// 		skip_spaces(&str, current_state);
// 		current_state = update_token_state(str, current_state);
// 		if (!*str)
// 			break ;
// 		new_token = create_token(str, current_state);
// 		lstadd_back_token(&lst, new_token);
// 		str += new_token->len;
// 	}
// 	return (lst);
// }

t_token	*tokenize(const char *str)
{
	t_token	*list;
	t_token	*new_token;

	list = NULL;
	while (*str)
	{
		skip_spaces(&str);
		if (!*str)
			break ;
		else if (*str == '|')
			new_token = read_pipe(&str);
		else if (*str == '&')
			new_token = read_ampersand(&str);
		else if (*str == '<' || *str == '>')
			new_token = read_redirect(&str);
		else if (*str == '\'')
			new_token = read_single_quote(&str);
		else if (*str == '\"')
			new_token = read_double_quote(&str);
		else
			new_token = read_general(&str);
		lstadd_back_token(&list, new_token);
	}
	return (list);
}

t_token	*lexer(const char *str)
{
	t_token	*token_list;

	if (!str)
		set_errno_and_exit("tokenize: str is NULL\n", EINVAL);
	token_list = tokenize(str);
	return (token_list);
}
