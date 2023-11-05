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
#include "../../includes/execute.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

/*
 * 目標: redirectの実装
 * 準目標: man dup
 * 準目標: man dup2
 * 準目標:
 */

//void	putsyserr_exit(const char *syscall_name)
//{
//	perror(syscall_name);
//	exit(FAILURE);
//}

int	close_stdfd(int stdfd)
{
	int	save_fd;

	save_fd = dup(stdfd);
	close(stdfd);
	return (save_fd);
}

void	restore_fd(int save_fd, int stdfd)
{
	dup2(save_fd, stdfd);
	close(save_fd);
}

//int	redirect_output(char *file)
//{
//	int	stdout_fd;
//
//	stdout_fd = dup(STDOUT_FILENO);
//	close(STDOUT_FILENO);
//	open(file, O_WRONLY|O_CREAT|O_TRUNC, 0644);
//	dup2(stdout_fd, STDOUT_FILENO);
//	close(stdout_fd);
//	return (0);
//}

/* > file */
//int	redirect_output(char *file)
//{
//	int	stdout_fd;
//
//	stdout_fd = dup(STDOUT_FILENO);
//	close(STDOUT_FILENO);
//	open(file, O_WRONLY|O_CREAT|O_TRUNC, 0644);
//	return (stdout_fd);
//}

/* > file */
int	*redirect_output(const char *file, int *fd)
{
	fd[0] = dup(STDOUT_FILENO);
	close(STDOUT_FILENO);
	fd[1] = open(file, O_WRONLY|O_CREAT|O_TRUNC, 0644);
	return (fd);
}

/* >> file */
//int	redirect_append(char *file)
//{
//	int	stdout_fd;
//
//	stdout_fd = dup(STDOUT_FILENO);
//	close(STDOUT_FILENO);
//	open(file, O_WRONLY|O_CREAT|O_APPEND, 0644);
//	return (stdout_fd);
//}

int	*redirect_append(const char *file, int *fd)
{
	fd[0] = dup(STDOUT_FILENO);
	close(STDOUT_FILENO);
	fd[1] = open(file, O_WRONLY|O_CREAT|O_APPEND, 0644);
	return (fd);
}

/* < file */
//int	redirect_input(char *file)
//{
//	int		stdin_fd;
//	int 	fd;
//
//	stdin_fd = dup(STDIN_FILENO);
//	close(STDIN_FILENO);
//	fd = open(file, O_RDONLY);
//	return (stdin_fd);
//}
int	*redirect_input(const char *file, int *fd)
{
	if (access(file, F_OK) == ERROR)
		puterr_exit(file, strerror(errno));
	fd[0] = dup(STDIN_FILENO);
	close(STDIN_FILENO);
	fd[1] = open(file, O_RDONLY);
	return (fd);
}

//int	redirect_std(char *file, int stdfd)
//{
//	int	save_fd;
//
//	if (stdfd > 3)
//		return (ERROR);
//	save_fd = dup(stdfd);
//	close(stdfd);
//}

//int	main(void)
//{
//	int *fd;
//
//	fd = ft_calloc(2, sizeof(int));
//	fd = redirect_output("file.txt", fd);
//	write(fd[1], "hello\n", 6);
//	restore_fd(fd[0], fd[1]);
//	write(fd[1], "hello\n", 6);
//	fd = redirect_append("file.txt", fd);
//	write(fd[1], "world\n", 6);
//	restore_fd(fd[0], fd[1]);
//	write(fd[1], "world\n", 6);
////	fd = redirect_input("file.txt", fd);
////	printf("fd[0]: %d, fd[1]: %d\n", fd[0], fd[1]);
//	return (0);
//}
