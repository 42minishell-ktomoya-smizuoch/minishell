/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:37:58 by ktomoya           #+#    #+#             */
/*   Updated: 2023/08/30 12:55:31 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

enum e_type	get_token_type(const char *str)
{
	enum e_type	type;

	if (*str == '|')
		type = TYPE_PIPE;
	else if (*str == '&')
		type = TYPE_AMPERSAND;
	else if (*str == '(')
		type = TYPE_LEFT_PARENTHESIS;
	else if (*str == ')')
		type = TYPE_RIGHT_PARENTHESIS;
	else if (*str == '<' || *str == '>')
		type = TYPE_REDIR;
	else if (*str == ' ')
		type = TYPE_SPACE;
	else if (*str == '\t')
		type = TYPE_TAB;
	else if (*str == '\n')
		type = TYPE_NEWLINE;
	else
		type = TYPE_GENERAL;
	return (type);
}

t_list	*tokenizer(const char *str)
{
	t_token_list	*head;
	t_token_list	*tmp;
	t_token			token;

	head = NULL;
	while (*str)
	{
		token.word = ft_strdup(str);
		token.type = get_token_type(str);
		tmp = ft_lstnew(token);
		ft_lstadd_back(&head, tmp);
		str++;
	}
	return (head);
}
