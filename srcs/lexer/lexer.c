/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:37:58 by ktomoya           #+#    #+#             */
/*   Updated: 2023/11/07 11:55:30 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/minishell.h"

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
	return (token);
}

// int	main(int argc, char **argv)
// {
// 	t_token		*token;
// 	t_token		*head;
// 	const char	*line;
// 	char 		*word;

// 	(void)argv;
// 	if (argc != 1)
// 		return (FAILURE);
// 	while (1)
// 	{
// 		line = readline("minishell$ ");
// 		if (*line)
// 			add_history(line);
// 		token = lexer(line);
// 		head = token;
// 		while (token)
// 		{
// 			word = ft_substr(token->str, 0, token->len);
// 			printf("type: %d, word: %s\n", token->type, word);
// 			free(word);
// 			token = token->next;
// 		}
// 		free((void *)line);
// 		free_token(head);
// 	}
// 	return (0);
// }
