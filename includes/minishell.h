/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smizuoch <smizuoch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:57:32 by kudoutomoya       #+#    #+#             */
/*   Updated: 2023/11/21 09:33:16 by smizuoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "lexer.h"
# include "parser.h"
# include "expansion.h"
# include "execute.h"
# include "pipe.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>

# define SUCCESS 0

int	g_signal;

//typedef struct s_env
//{
//	char			*key;
//	struct s_env	*next;
//	struct s_env	*prev;
//}	t_env;

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

t_token	*lexer(const char *str);

t_node	*parser(t_token *tokens);

void	print_ast(t_node *root);
void	print_argument_list(t_node *node, int depth);
void	print_node_tree(t_node *node, int depth);
void	print_redirect_list(t_node *node, int depth);
void 	print_node(t_node *node, int depth);

int		set_signal(int mode);
void	check_signal(t_env *env);

void	handler_exec(int signum);
void	handler_heardoc(int signum);
void	handler_sigint(int signum);

int		pipe_cmd(t_node *ast, t_env *env);

extern int g_signal;

#endif
