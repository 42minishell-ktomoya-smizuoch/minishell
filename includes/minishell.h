/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:47:22 by ktomoya           #+#    #+#             */
/*   Updated: 2023/08/31 17:31:49 by ktomoya          ###   ########.fr       */
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
	TYPE_LEFT_PARENTHESIS,
	TYPE_RIGHT_PARENTHESIS,
	TYPE_REDIR,
	TYPE_NEWLINE,
	TYPE_QUOTE,
	TYPE_DOUBLE_QUOTE
};

typedef struct s_token
{
	char			*word;
	size_t			len;
	enum e_type		type;
	enum e_state	state;
	struct s_token	*next;
}	t_token;

// typedef struct s_token_list
// {
// 	struct s_token_list	*next;
// 	t_token				*token;
// }	t_token_list;

int				display_prompt(void);
void			launch_executable(const char *exe_path);
t_token			*tokenize(const char *str);
void			set_errno_and_exit(const char *err_msg, int errno_num);
t_token			*create_token(const char *str);
void			lstadd_back_token(t_token **lst, t_token *new);
enum e_type		get_token_type(const char *str);
char			*get_token_word(const char *str);

#endif
