/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_errno_and_exit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 15:49:22 by ktomoya           #+#    #+#             */
/*   Updated: 2023/09/03 15:49:45 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_errno_and_exit(const char *str, int errnum)
{
	errno = errnum;
	ft_putstr_fd(str, STDERR_FILENO);
	exit(errnum);
}
