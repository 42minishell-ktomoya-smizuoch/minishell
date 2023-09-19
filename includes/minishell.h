/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:47:22 by ktomoya           #+#    #+#             */
/*   Updated: 2023/09/18 12:48:28 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

# define SUCCESS 0

typedef enum e_type
{
	TYPE_GENERAL,
	TYPE_PIPE,
	TYPE_AMPERSAND,
	TYPE_REDIRECT,
	TYPE_EOF,
	TYPE_NEWLINE,
}	t_type;

typedef enum e_node_kind
{
	NODE_ARGUMENT,
	NODE_PIPE,
	NODE_AMPERSAND,
	NODE_REDIRECT,
}	t_node_kind;

typedef struct s_token
{
	t_type			type;
	struct s_token	*head;
	struct s_token	*cur;
	struct s_token	*next;
	const char		*str;
	size_t			len;
}	t_token;

//typedef struct s_node
//{
//	t_node_kind			kind;
//	struct s_node	*first_child;
//	struct s_node	*next_sibling;
//	const char			*str;
//	size_t				len;
//}	t_node;

//typedef struct s_node
//{
//	t_node_kind		kind;
//	struct s_node	*left;
//	struct s_node	*right;
//	const char		*str;
//	size_t			len;
//}	t_node;

typedef struct s_node
{
	t_node_kind		kind;
	struct s_node	*left;
	struct s_node	*right;
	const char		*word;
}	t_node;


int		display_prompt(void);
void	launch_executable(const char *exe_path);
t_token	*lexer(const char *str);
void	set_errno_and_exit(const char *str, int errnum);

t_node	*parser(t_token *tokens);

void	print_ast(t_node *root);
void	print_argument_list(t_node *node, int depth);
void	print_node_tree(t_node *node, int depth);

#endif
