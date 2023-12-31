/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:53:58 by kudoutomoya       #+#    #+#             */
/*   Updated: 2023/11/25 10:22:27 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/redirect.h"
#include "../../includes/execute.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

void	restore_fd(int save_fd, int stdfd)
{
	dup2(save_fd, stdfd);
	close(save_fd);
}

/* > file */
int	redirect_output(const char *file, int fd[4])
{
	int	check_fd;

	if (!file || *file == '\0')
	{
		puterr("\0", strerror(ENOENT));
		return (ERROR);
	}
	if (fd[2] != fd[3])
		restore_fd(fd[2], fd[3]);
	check_fd = open(file, O_WRONLY | O_CREAT, 0644);
	if (check_fd == ERROR)
		return (perror_retint(file, ERROR));
	if (close(check_fd) == ERROR)
		return (perror_retint("close", ERROR));
	fd[2] = dup(STDOUT_FILENO);
	if (fd[2] == ERROR)
		return (perror_retint("dup", ERROR));
	if (close(STDOUT_FILENO) == ERROR)
		return (perror_retint("close", ERROR));
	fd[3] = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd[3] == ERROR)
		return (perror_retint("open", ERROR));
	return (SUCCESS);
}

/* >> file */
int	redirect_append(const char *file, int fd[4])
{
	int	check_fd;

	if (!file || *file == '\0')
	{
		puterr("\0", strerror(ENOENT));
		return (ERROR);
	}
	if (fd[2] != fd[3])
		restore_fd(fd[2], fd[3]);
	check_fd = open(file, O_WRONLY | O_CREAT, 0644);
	if (check_fd == ERROR)
		return (perror_retint(file, ERROR));
	if (close(check_fd) == ERROR)
		return (perror_retint("close", ERROR));
	fd[2] = dup(STDOUT_FILENO);
	if (fd[2] == ERROR)
		return (perror_retint("dup", ERROR));
	if (close(STDOUT_FILENO) == ERROR)
		return (perror_retint("close", ERROR));
	fd[3] = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd[3] == ERROR)
		return (perror_retint("open", ERROR));
	return (SUCCESS);
}

int	redirect_input(const char *file, int fd[4])
{
	int	check_fd;

	if (!file || *file == '\0')
	{
		puterr("\0", strerror(ENOENT));
		return (ERROR);
	}
	if (fd[0] != fd[1])
		restore_fd(fd[0], fd[1]);
	check_fd = open(file, O_RDONLY);
	if (check_fd == ERROR)
		return (perror_retint(file, ERROR));
	if (close(check_fd) == ERROR)
		return (perror_retint("close", ERROR));
	fd[0] = dup(STDIN_FILENO);
	if (fd[0] == ERROR)
		return (perror_retint("dup", ERROR));
	if (close(STDIN_FILENO) == ERROR)
		return (perror_retint("close", ERROR));
	fd[1] = open(file, O_RDONLY);
	if (fd[1] == ERROR)
		return (perror_retint("open", ERROR));
	return (SUCCESS);
}

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
