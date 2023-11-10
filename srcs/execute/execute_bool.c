/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bool.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kudoutomoya <kudoutomoya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 14:02:23 by kudoutomoya       #+#    #+#             */
/*   Updated: 2023/10/14 14:05:43 by kudoutomoya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

bool	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0)
		return (true);
	return (false);
}

bool	is_directory(char *path)
{
	struct stat	buf;

	if (stat(path, &buf) == ERROR)
		putsyserr_exit("stat");
	if (S_ISDIR(buf.st_mode))
		return (true);
	return (false);
}

bool    directory_exists(char *path)
{
    struct stat buf;
    char        *endp;
    char        *dir;

    endp = path;
    endp = ft_strrchr(endp, '/');
    // スラッシュがなければディレクトリではない。カレントディレクトリなので存在する。
    if (!endp)
        return (true);
    dir = ft_substr(path, 0, endp - path);
    if (stat(dir, &buf) == ERROR)
    {
        puterr(path, strerror(errno)); // Todo: exitしないputsyserr関数を作る
        free(dir);
        return (false);
    }
    free(dir);
    if (S_ISDIR(buf.st_mode))
        return (true);
    return (false);
}