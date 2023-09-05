/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kudoutomoya <kudoutomoya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:47:22 by ktomoya           #+#    #+#             */
/*   Updated: 2023/09/05 14:14:25 by kudoutomoya      ###   ########.fr       */
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

typedef struct s_token
{
	char			*word;
	enum e_type		type;
	// size_t			len;
	struct s_token	*next;
}	t_token;

// typedef struct s_token_list
// {
// 	struct s_token_list	*next;
// 	t_token				*token;
// }	t_token_list;

int				display_prompt(void);
void			launch_executable(const char *exe_path);
t_token			*lexer(const char *str);
void			set_errno_and_exit(const char *err_msg, int errno_num);
t_token			*create_token(const char *str, size_t token_len);
void			lstadd_back_token(t_token **lst, t_token *new);
// enum e_type		get_token_type(const char *str);
// size_t			get_token_len(const char *str, enum e_state current);
void			skip_spaces(const char **str);
enum e_state	update_state(const char c, enum e_state state);
bool			is_space_or_tab(char c);
void			set_errno_and_exit(const char *str, int errnum);
t_token			*read_pipe(const char c);
t_token			*read_ampersand(const char c);
t_token			*read_redirect(const char *str);
t_token			*read_single_quote(const char *str);
t_token			*read_double_quote(const char *str);
t_token			*read_general(const char *str);
// t_token			*read_quoted(const char *str);
enum e_type		get_token_type(const char *str);
size_t			get_double_quoted_size(const char *str);
size_t			get_redirect_len(const char *str);
size_t			get_token_len(const char *str);
size_t			get_general_len(const char *str);

#endif
