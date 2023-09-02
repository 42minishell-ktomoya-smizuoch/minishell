/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kudoutomoya <kudoutomoya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:37:58 by ktomoya           #+#    #+#             */
/*   Updated: 2023/09/01 22:07:16 by kudoutomoya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_metachar(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '|' || c == '&'
		|| c == '(' || c == ')' || c == '<' || c == '>' || c == '\''
		|| c == '\"');
}

// char	*get_token_word(const char *str, enum e_state prev_state)
// {
// 	char	*word;
// 	size_t	len;

// 	len = 0;
// 	if (is_metachar(*str))
// 		len++;
// 	else
// 	{
// 		while (str[len] && !is_metachar(str[len]))
// 			len++;
// 	}
// 	word = ft_substr(str, 0, len);
// 	return (word);
// }

bool	is_space_or_tab(char c)
{
	return (c == ' ' || c == '\t');
}

bool	is_metachar_except_space(char c)
{
	return (c == '\n' || c == '|' || c == '&' || c == '(' || c == ')'
		|| c == '<' || c == '>' || c == '\'' || c == '\"');
}

char	*get_token_word(const char *str, enum e_state prev)
{
	char	*word;
	size_t	len;

	len = 0;
	if (prev == STATE_IN_QUOTE || prev == STATE_IN_DOUBLE_QUOTE)
	{
		// メタ文字以外、ただし、スペースとタブは除くときlen++
		while (str[len] && !is_metachar_except_space(str[len]))
			len++;
	}
	else
	{
		if (is_space_or_tab(*str))
			len++;
		else
		{
			while (str[len] && !is_metachar(str[len]))
				len++;
		}
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

void	skip_spaces(const char **str, enum e_state prev)
{
	if (prev == STATE_GENERAL)
	{
		while (**str && is_space_or_tab(**str))
			(*str)++;
	}
}

t_token	*tokenize(const char *str)
{
	t_token			*new_token;
	t_token			*head;
	enum e_state	current;

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
