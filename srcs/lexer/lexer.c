/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:37:58 by ktomoya           #+#    #+#             */
/*   Updated: 2023/09/15 13:41:22 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	skip_spaces(const char **str)
{
	while (is_blank(**str))
		(*str)++;
}

// static t_token	*tokenize(const char *str)
// {
// 	t_token	*head;
// 	size_t	token_len;
// 	t_token	*token;

// 	head = NULL;
// 	while (*str)
// 	{
// 		skip_spaces(&str);
// 		if (!*str)
// 			break ;
// 		token_len = get_token_len(str);
// 		if (!token_len)
// 			continue ;
// 		token = create_token(str, token_len);
// 		if (!token)
// 			set_errno_and_exit("tokenize: token is NULL\n", ENOMEM);
// 		lstadd_back_token(&head, token);
// 		str += token_len;
// 	}
// 	return (head);
// }

static t_token	*tokenize(const char *str)
{
	t_token	*head;
	t_token	*token;

	head = NULL;
	while (*str)
	{
		skip_spaces(&str);
		if (*str == '\0')
			break ;
		token = create_token(str);
		if (!token)
			exit(1);
		lstadd_back_token(&head, token);
		str += token->len;
	}
	return (head);
}

t_token	*lexer(const char *str)
{
	t_token	*token;

	if (!str)
		ft_putendl_fd("lexer: str is NULL", STDERR_FILENO);
	token = tokenize(str);
	return (token);
}
