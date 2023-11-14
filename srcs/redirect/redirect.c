/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:53:58 by kudoutomoya       #+#    #+#             */
/*   Updated: 2023/11/14 11:25:37 by ktomoya          ###   ########.fr       */
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
// int	redirect_output(const char *file, int fd[2])
int *redirect_output(const char *file, int *fd)
{
    // if (is_directory((char *)file))
    // {
    //     puterr(file, strerror(EISDIR));
    //     free(fd);
    //     return (NULL);
    // }
    // if (access(file, W_OK) == ERROR && errno != ENOENT)
    // {
    //     puterr(file, strerror(errno));
    //     free(fd);
    //     return (NULL);
    // }
    // struct stat buf;
    // char        *dir = NULL;
    // char        *endp;
    // mode_t      mode;

    // endp = ft_strrchr(file, '/');
    // /がある場合
    // if (endp)
    // {
    //     dir = ft_substr(file, 0, endp - file);
    //     printf("endp: %s\n", endp);
    //     printf("endp - file: %zu\n", endp - file + 1);
    //     printf("dir: %s\n", dir);
    //     // if (stat(dir, &buf) == ERROR)
    //     // {
    //     //     write(1, "aaaaa\n", 6);
    //     //     puterr(file, strerror(errno));
    //     //     free(fd);
    //     //     return (NULL);
    //     // }
    //     if (stat(dir, &buf))
    //         perror("stat: ");
    //     mode = buf.st_mode;
    //     if (S_ISDIR(mode))
    //     {
    //         // puterr(file, strerror(EISDIR));
    //         // free(fd);
    //         // return (NULL);
    //         if (!(mode & S_IXUSR))
    //         {
    //             puterr(file, strerror(EACCES));
    //             free(fd);
    //             return (NULL);
    //         }
    //     }
        
    //     free(dir);
    // }
    fd[0] = dup(STDOUT_FILENO);
    // if (fd[0])
    //     return (NULL);        
    if (close(STDOUT_FILENO) == ERROR)
    {
        perror("minishell: dup(): ");
        free(fd);
        return (NULL);
    }
    fd[1] = open(file, O_WRONLY|O_CREAT|O_TRUNC, 0644);
    if (fd[1] == ERROR)
    {
        perror(file);
        free(fd);
        printf("aaaaa\n");
        return (NULL);
    }
    return (fd);
	// fd[0] = dup(STDOUT_FILENO);
	// close(STDOUT_FILENO);
	// fd[1] = open(file, O_WRONLY|O_CREAT|O_TRUNC, 0644);
	// return (fd);
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
    if (is_directory((char *)file))
    {
        puterr(file, strerror(EISDIR));
        free(fd);
        return (NULL);
    }
    if (access(file, W_OK) == ERROR && errno != ENOENT)
    {
        puterr(file, strerror(errno));
        free(fd);
        return (NULL);
    }
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
    if (is_directory((char *)file))
    {
        puterr(file, strerror(EISDIR));
        free(fd);
        return (NULL);
    }
    if (access(file, R_OK) == ERROR)
    {
        puterr(file, strerror(errno));
        free(fd);
        return (NULL);
    }
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
