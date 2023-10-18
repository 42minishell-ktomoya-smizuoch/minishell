/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kudoutomoya <kudoutomoya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:53:58 by kudoutomoya       #+#    #+#             */
/*   Updated: 2023/10/17 09:54:00 by kudoutomoya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/redirect.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

/*
 * 目標: redirectの実装
 * 準目標: man dup
 * 準目標: man dup2
 */

void	putsyserr_exit(const char *syscall_name)
{
	perror(syscall_name);
	exit(FAILURE);
}

/*
 * > filename
 */
void	redirect_output(char *file)
{
	int	fd = open(file, O_WRONLY|O_CREAT|O_TRUNC, 0644);
	if (fd == ERROR)
		putsyserr_exit("open");
	int result = dup2(fd, STDOUT_FILENO);
	if (result == ERROR)
		putsyserr_exit("dup2");
	return (result);
}