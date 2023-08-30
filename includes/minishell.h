/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:47:22 by ktomoya           #+#    #+#             */
/*   Updated: 2023/08/30 11:37:58 by ktomoya          ###   ########.fr       */
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

typedef enum
{
	TYPE_GENERAL,
	TYPE_PIPE,
	TYPE_AMPERSAND,
	TYPE_LEFT_PARENTHESIS,
	TYPE_RIGHT_PARENTHESIS,
	TYPE_REDIR,
	TYPE_SPACE,
	TYPE_TAB,
	TYPE_NEWLINE
}	e_type;

typedef struct s_token
{
	char		*word;
	e_type		type;
}	t_token;

typedef struct s_list
{
	struct s_list	*next;
	t_token			token;
}	t_list;

int		display_prompt(void);
void	launch_executable(const char *exe_path);

#endif
