/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:47:22 by ktomoya           #+#    #+#             */
/*   Updated: 2023/09/12 16:07:39 by ktomoya          ###   ########.fr       */
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

enum e_state
{
	STATE_GENERAL,
	STATE_IN_QUOTE,
	STATE_IN_DOUBLE_QUOTE
};

enum e_type
{
	TYPE_GENERAL,
	TYPE_PIPE,
	TYPE_AMPERSAND,
	TYPE_REDIRECT
};

typedef enum e_node_kind
{
	NODE_GENERAL,
	NODE_PIPE,
	NODE_AMPERSAND,
	NODE_REDIRECT,
	NODE_COMMAND,
	NODE_ARGUMENT,
	NODE_FILE,
	NODE_ENV,
	NODE_ENV_KEY,
	NODE_ENV_VALUE
}	t_node_kind;

typedef struct s_token
{
	char			*word;
	enum e_type		type;
	struct s_token	*next;
}	t_token;

typedef struct s_ast
{
	t_node_kind		kind;
	char			*data;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

int				display_prompt(void);
void			launch_executable(const char *exe_path);
t_token			*lexer(const char *str);
size_t			get_token_len(const char *str);
t_token			*create_token(const char *str, size_t token_len);
void			lstadd_back_token(t_token **lst, t_token *new);
bool			is_blank(char c);
bool			is_metachar(const char c);
void			set_errno_and_exit(const char *str, int errnum);

#endif
