/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kudoutomoya <kudoutomoya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:37:58 by ktomoya           #+#    #+#             */
/*   Updated: 2023/09/05 13:05:49 by kudoutomoya      ###   ########.fr       */
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

// t_token	*tokenize(const char *str)
// {
// 	t_token	*list;
// 	t_token	*new_token;

// 	list = NULL;
// 	while (*str)
// 	{
// 		skip_spaces(&str);
// 		if (!*str)
// 			break ;
// 		else if (*str == '|')
// 			new_token = read_pipe(*str);
// 		else if (*str == '&')
// 			new_token = read_ampersand(*str);
// 		else if (*str == '<' || *str == '>')
// 			new_token = read_redirect(str);
// 		// else if (*str == '\'')
// 		// 	new_token = read_single_quote(str);
// 		// else if (*str == '\"')
// 		// 	new_token = read_double_quote(str);
// 		// else if (is_quoted(*str))
// 		// 	new_token = read_quoted(str);
// 		else
// 			new_token = read_general(str);
// 		new_token->word = ft_substr(str, 0, new_token->len);
// 		lstadd_back_token(&list, new_token);
// 		str += new_token->len;
// 	}
// 	return (list);
// }

t_token	*create_token_list(const char *str)
{
	t_token	*list;
	size_t	token_len;
	t_token	*token;

	list = NULL;
	while (*str)
	{
		skip_spaces(&str);
		if (!*str)
			break ;
		token_len = get_token_len(str);
		if (!token_len)
			continue ;
		token = create_token(str, token_len);
		if (!token)
			set_errno_and_exit("create_token_list: token is NULL\n", ENOMEM);
		lstadd_back_token(&list, token);
		str += token_len;
	}
	return (list);
}

t_token	*lexer(const char *str)
{
	t_token	*token_list;

	if (!str)
		ft_putendl_fd("lexer: str is NULL", STDERR_FILENO);
	token_list = create_token_list(str);
	return (token_list);
}
