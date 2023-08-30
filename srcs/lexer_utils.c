/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:17:52 by ktomoya           #+#    #+#             */
/*   Updated: 2023/08/30 19:05:33 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_errno_and_exit(const char *err_msg, int errno_num)
{
	errno = errno_num;
	ft_putstr_fd(err_msg, STDERR_FILENO);
}

// t_token *create_token(void *content)
// {
// 	t_token *new;

// 	new = (t_token *)malloc(sizeof(t_token));
// 	if (!new)
// 		set_errno_and_exit("malloc error\n", ENOMEM);
	
// }
