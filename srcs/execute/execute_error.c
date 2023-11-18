/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 13:52:35 by kudoutomoya       #+#    #+#             */
/*   Updated: 2023/11/18 09:26:00 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	puterr(const char *input, const char *msg)
{
	ft_putstr_fd(input, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
}

void	puterr_len(const char *input, size_t n, const char *msg)
{
	write(STDERR_FILENO, input, n);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
}

void	puterr_exit(const char *input, const char *msg, int exit_status)
{
	ft_putstr_fd(input, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	exit(exit_status);
}

int	putsyserr_retint(const char *syscall, int retnum)
{
	perror(syscall);
	return (retnum);
}

void	putsyserr_exit(const char *syscall_name)
{
	perror(syscall_name);
	exit(FAILURE);
}
