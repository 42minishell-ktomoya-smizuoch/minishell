/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:53:58 by kudoutomoya       #+#    #+#             */
/*   Updated: 2023/10/18 20:36:09 by ktomoya          ###   ########.fr       */
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
 * 準目標:
 */

void	putsyserr_exit(const char *syscall_name)
{
	perror(syscall_name);
	exit(FAILURE);
}

/* > file */
int	redirect_output(char *file)
{
	int	stdout_fd;

	stdout_fd = dup(STDOUT_FILENO);
	close(STDOUT_FILENO);
	open(file, O_WRONLY|O_CREAT|O_TRUNC, 0644);
	write(STDOUT_FILENO, "hello, world\n", 13);
	dup2(stdout_fd, STDOUT_FILENO);
	close(stdout_fd);
	return (0);
}

/* >> file */
int	redirect_append(char *file)
{
	int	stdout_fd;

	stdout_fd = dup(STDOUT_FILENO);
	close(STDOUT_FILENO);
	open(file, O_WRONLY|O_CREAT|O_APPEND, 0644);
	write(STDOUT_FILENO, "hello, world\n", 13);
	dup2(stdout_fd, STDOUT_FILENO);
	close(stdout_fd);
	return (0);
}

/* < file */
int	redirect_input(char *file)
{
	int		stdin_fd;
	int 	fd;
	char	buf[256];

	stdin_fd = dup(STDIN_FILENO);
	close(STDIN_FILENO);
	fd = open(file, O_RDONLY);
	/* 処理内容 */
	while (read(STDIN_FILENO, buf, 256) < 0)
		;
	printf("%s", buf);
	/* fdを元に戻す */
	dup2(stdin_fd, STDIN_FILENO);
	close(stdin_fd);
	return (0);
}

int	main(void)
{	
	redirect_input("test.txt");
	return (0);
}
