/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:37:58 by ktomoya           #+#    #+#             */
/*   Updated: 2023/08/31 18:47:48 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_metachar(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '|' || c == '&'
		|| c == '(' || c == ')' || c == '<' || c == '>' || c == '\''
		|| c == '\"');
}

char	*get_token_word(const char *str)
{
	char	*word;
	size_t	len;

	len = 0;
	if (is_metachar(*str))
		len++;
	else
	{
		while (str[len] && !is_metachar(str[len]))
			len++;
	}
	word = ft_substr(str, 0, len);
	return (word);
}

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
	else if (*str == '\n')
		type = TYPE_NEWLINE;
	else if (*str == '\'')
		type = TYPE_QUOTE;
	else if (*str == '\"')
		type = TYPE_DOUBLE_QUOTE;
	else
		type = TYPE_GENERAL;
	return (type);
}

void	skip_spaces(const char **str)
{
	while (**str == ' ' || **str == '\t')
		(*str)++;
}

t_token	*tokenize(const char *str)
{
	t_token	*new_token;
	t_token	*head;

	if (!str)
		set_errno_and_exit("tokenize: str is NULL\n", EINVAL);
	head = NULL;
	new_token = create_token(str, STATE_GENERAL);
	while (*str)
	{
		lstadd_back_token(&head, new_token);
		str += new_token->len;
		new_token = create_token(str, new_token->state);
	}
	return (head);
}
