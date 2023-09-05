/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kudoutomoya <kudoutomoya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:47:22 by ktomoya           #+#    #+#             */
/*   Updated: 2023/09/05 14:52:02 by kudoutomoya      ###   ########.fr       */
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
size_t			get_token_len(const char *str);
t_token			*create_token(const char *str, size_t token_len);
void			set_errno_and_exit(const char *err_msg, int errno_num);
void			lstadd_back_token(t_token **lst, t_token *new);
bool			is_space_or_tab(char c);
void			set_errno_and_exit(const char *str, int errnum);

#endif
