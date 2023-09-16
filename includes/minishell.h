/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:47:22 by ktomoya           #+#    #+#             */
/*   Updated: 2023/09/15 14:24:34 by ktomoya          ###   ########.fr       */
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
	TYPE_EOF,
	TYPE_NEWLINE,
}	t_type;

typedef enum e_node_kind
{
	NODE_COMMAND,
	NODE_ARGUMENT,
	NODE_PIPE,
	NODE_AMPERSAND,
	NODE_REDIRECT,
}	t_node_kind;

typedef struct s_token
{
	t_type			type;
	struct s_token	*next;
	struct s_token	*cur;
	const char		*str;
	size_t 			len;
}	t_token;

typedef struct s_node_tree
{
	t_node_kind			kind;
	struct s_node_tree	*first_child;
	struct s_node_tree	*next_sibling;
	const char			*str;
	size_t				len;
}	t_node_tree;

int				display_prompt(void);
void			launch_executable(const char *exe_path);
t_token			*lexer(const char *str);
void			set_errno_and_exit(const char *str, int errnum);

t_node_tree		*parser(t_token *tokens);

#endif
