/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 22:16:56 by kudoutomoya       #+#    #+#             */
/*   Updated: 2023/09/18 19:17:25 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/minishell.h"

/*
 * 目標: cmd_suffixの文法を実装する
 * 準目標:
 */

/*
 * リダイレクトの文法
 * コマンド名　引数1 引数2 ... 引数n <リダイレクト1> <リダイレクト2> ... <リダイレクトn>
 */

//void	*syntax_error_null(const char *token)
//{
//	ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
//	ft_putstr_fd(token, STDERR_FILENO);
//	ft_putendl_fd("'", STDERR_FILENO);
//	return (NULL);
//}

void	put_syntax_error(t_token *tok)
{
	char	input[100000];

	ft_memset(input, 0, 100000);
	if (tok && (tok->type == TYPE_GENERAL || tok->type == TYPE_DOLLAR))
		ft_memcpy(input, tok->str, tok->len);
	ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
	if (tok && tok->type == TYPE_PIPE)
		ft_putstr_fd("|", STDERR_FILENO);
	else if (tok && tok->type == TYPE_GREAT)
		ft_putstr_fd(">", STDERR_FILENO);
	else if (tok && tok->type == TYPE_LESS)
		ft_putstr_fd("<", STDERR_FILENO);
	else if (tok && tok->type == TYPE_DGREAT)
		ft_putstr_fd(">>", STDERR_FILENO);
	else if (tok && tok->type == TYPE_DLESS)
		ft_putstr_fd("<<", STDERR_FILENO);
	else if (tok && (tok->type == TYPE_GENERAL || tok->type == TYPE_DOLLAR))
		ft_putstr_fd(input, STDERR_FILENO);
	else if (tok && tok->type == TYPE_EOF)
		ft_putstr_fd("newline", STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
}

void	*syntax_error_null(t_token *tok)
{
	put_syntax_error(tok);
	return (NULL);
}

/*
 * pipeline = command ('|' command)*
 */
t_node	*command_line(t_token *tok, int *flag)
{
	t_node	*node;

	if (!expect(TYPE_GENERAL, tok) && !expect(TYPE_DOLLAR, tok))
	{
		if (expect_next(TYPE_GENERAL, tok) && expect_next(TYPE_GENERAL, tok))
			return (syntax_error_null(tok->cur));
		else
			return (syntax_error_null(tok->cur->next));
	}
	node = command(tok, flag);
	if (!node)
		return (NULL);
	while (1)
	{
		if (consume(TYPE_PIPE, tok))
		{
			if (expect(TYPE_GENERAL, tok) || expect(TYPE_DOLLAR, tok))
			{
				node = new_branch(NODE_PIPE, node, command(tok, flag));
				if (!node)
				{
					*flag = ERROR;
					return (NULL);
				}
			}
			else
			{
				*flag = ERROR;
				put_syntax_error(tok->cur);
				return (node);
			}
		}
		else
			return (node);
	}
}

/*
 * simple_command ::= cmd_name word_list?
 * word_list ::= word+
 */
//t_node	*command(t_token *tok)
//{
//	t_node	*cmd;
//	t_token	*cur;
//	t_node	*node;
//
//	cmd = NULL;
//	cur = tok->cur;
//	while (cur->type != TYPE_EOF && cur->type != TYPE_PIPE)
//	{
//		node = new_node(NODE_ARGUMENT);
//		if (!node)
//		{
//			// Todo: 構文木をfreeする関数を作る
//			return (NULL);
//		}
//		node->word = ft_substr(cur->str, 0, cur->len);
//		if (node->word == NULL)
//		{
//			// Todo: freeする
//			return (NULL);
//		}
//		lstadd_back_node(&cmd, node);
//		cur = cur->next;
//	}
//	tok->cur = cur;
//	return (cmd);
//}

/* command ::= cmd_name cmd_suffix? */
/* cmd_name ::= WORD */
//t_node	*command(t_token *tok)
//{
//	t_token	*cur;
//	t_node	*cmd;
//	t_node	*node;
//
//	cur = tok->cur;
//	cmd = new_node(NODE_COMMAND);
//	node->word = ft_substr(cur->str, 0, cur->len);
//	while (1)
//	{
//		if (cur->type == TYPE_PIPE
//			|| cur->type == TYPE_EOF)
//			break ;
//		else
//			node = cmd_suffix
//	}
//	return (node);
//}

/* cmd_suffix ::= (io_redirect | WORD)+ */
//t_node	*cmd_suffix(t_token *tok)
//{
//	t_token	*cur;
//	t_node	*node;
//	t_node	*suffix;
//
//	node = NULL;
//	suffix = NULL;
//	while (1)
//	{
//		cur = tok->cur;
//		if (cur->type == TYPE_LESS
//			|| cur->type == TYPE_GREAT
//			|| cur->type == TYPE_DLESS
//			|| cur->type == TYPE_DGREAT)
//			node = io_redirect(tok);
//		else if (cur->type == TYPE_GENERAL)
//		{
//			node = new_node(NODE_ARGUMENT);
//			node->word = ft_substr(cur->str, 0, cur->len);
//			tok->cur = cur->next;
//		}
//		else
//			break ;
//		lstadd_back_node(&suffix, node);
//	}
//	tok->cur = cur->next;
//	return (suffix);
//}

/* command ::= cmd_args io_redirects */
t_node	*command(t_token *tok, int *flag)
{
	t_node	*cmd;
	t_node	*redirects;

	if (*flag == ERROR)
		return (NULL);
	cmd = cmd_args(tok, flag);
	if (!cmd)
		return (NULL);
	redirects = io_redirects(tok, flag);
	lstadd_back_node(&cmd, redirects);
	return (cmd);
}

/* cmd_args ::= cmd_arg cmd_args* */
t_node	*cmd_args(t_token *tok, int *flag)
{
	t_node	*args;
	t_node	*arg;

	args = cmd_arg(tok, flag);
	if (!args)
		return (NULL);
	while (expect(TYPE_GENERAL, tok) || expect(TYPE_DOLLAR, tok))
	{
		arg = cmd_arg(tok, flag);
		if (!arg)
			break ;
		lstadd_back_node(&args, arg);
	}
	return (args);
}

/* cmd_arg ::= WORD */
t_node	*cmd_arg(t_token *tok, int *flag)
{
	t_node	*arg;

	if (expect(TYPE_EOF, tok) || *flag == ERROR)
		return (NULL);
	arg = new_node(NODE_ARGUMENT);
	if (!arg)
	{
		*flag = ERROR;
		return (NULL);
	}
	set_node_value(arg, tok->cur->str, tok->cur->len);
	if (consume(TYPE_GENERAL, tok) || consume(TYPE_DOLLAR, tok))
		;
	return (arg);
}

/* io_redirects ::= io_redirect* */
t_node	*io_redirects(t_token *tok, int *flag)
{
	t_node	*list;
	t_node	*node;

	if (expect(TYPE_EOF, tok) || *flag == ERROR)
		return (NULL);
	list = NULL;
	while (expect(TYPE_LESS, tok)
		   || expect(TYPE_GREAT, tok)
		   || expect(TYPE_DLESS, tok)
		   || expect(TYPE_DGREAT, tok))
	{
		node = io_redirect(tok, flag);
		if (!node)
			break ;
		lstadd_back_node(&list, node);
	}
	return (list);
}

/* io_redirect ::= io_file | io_here */
t_node	*io_redirect(t_token *tok, int *flag)
{
	t_node	*node;

	if (expect(TYPE_EOF, tok) || *flag == ERROR)
		return (NULL);
	node = NULL;
	if (expect(TYPE_LESS, tok)
		|| expect(TYPE_GREAT, tok)
		|| expect(TYPE_DGREAT, tok))
		node = io_file(tok, flag);
	else if (consume(TYPE_DLESS, tok))
		node = io_here(tok, flag);
	return (node);
}

/*
 * io_file ::= ('<' | '>' | '>>') filename
 */
t_node	*io_file(t_token *tok, int *flag)
{
	t_node	*node;

	node = NULL;
	if (consume(TYPE_LESS, tok))
		node = new_node(NODE_LESS);
	else if (consume(TYPE_GREAT, tok))
		node = new_node(NODE_GREAT);
	else if (consume(TYPE_DGREAT, tok))
		node = new_node(NODE_DGREAT);
	if (!node)
	{
		*flag = ERROR;
		return (NULL);
	}
	if (expect(TYPE_GENERAL, tok) || expect(TYPE_DOLLAR, tok))
	{
		if (expect_next(TYPE_GENERAL, tok) || expect_next(TYPE_DOLLAR, tok))
		{
			*flag = ERROR;
			free(node);
			return (syntax_error_null(tok->cur->next));
		}
		set_node_value(node, tok->cur->str, tok->cur->len);
		if (consume(TYPE_GENERAL, tok) || consume(TYPE_DOLLAR, tok))
			return (node);
	}
	else
	{
		*flag = ERROR;
		free(node);
		return (syntax_error_null(tok->cur));
	}
	return (node);
}

/* '<<' here_end */
t_node	*io_here(t_token *tok, int *flag)
{
	t_node	*node;

	node = NULL;
	if (expect(TYPE_GENERAL, tok) || expect(TYPE_DOLLAR, tok))
	{
		if (expect_next(TYPE_GENERAL, tok) || expect_next(TYPE_DOLLAR, tok))
		{
			*flag = ERROR;
			return (syntax_error_null(tok->cur->next));
		}
		node = new_node(NODE_DLESS);
		if (!node)
		{
			*flag = ERROR;
			return (NULL);
		}
		set_node_value(node, tok->cur->str, tok->cur->len);
		if (consume(TYPE_GENERAL, tok) || consume(TYPE_DOLLAR, tok))
			return (node);
	}
	else
	{
		*flag = ERROR;
		return (syntax_error_null(tok->cur));
	}
	return (node);
}
