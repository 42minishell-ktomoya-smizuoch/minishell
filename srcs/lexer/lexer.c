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

#include "../../includes/lexer.h"

static void	skip_spaces(const char **str)
{
	while (is_blank(**str))
		(*str)++;
}

void	*perror_null(const char *syscall)
{
	perror(syscall);
	return (NULL);
}

void	free_token(t_token *token)
{
	if (!token)
		return ;
	free_token(token->next);
	free(token);
}

t_token *free_token_null(t_token *head)
{
	free_token(head);
	return (NULL);
}

static t_token	*tokenize(const char *str)
{
	t_token	*head;
	t_token	*token;

	head = NULL;
	while (1)
	{
		skip_spaces(&str);
		if (*str == '\0' && head == NULL)
			break ;
		token = create_token(str);
		if (!token)
			return (free_token_null(head));
		lstadd_back_token(&head, token);
		if (token->type == TYPE_EOF)
			break ;
		str += token->len;
	}
	return (head);
}

t_token	*lexer(const char *str)
{
	t_token	*token;

	if (!str)
		return (NULL);
	token = tokenize(str);
	if (!token)
		return (NULL);
	return (token);
}
