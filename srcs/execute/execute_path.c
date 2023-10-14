/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kudoutomoya <kudoutomoya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 14:14:21 by kudoutomoya       #+#    #+#             */
/*   Updated: 2023/10/14 14:16:50 by kudoutomoya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

void	execute_abspath(char *const argv[], t_env *env)
{
	if (access(argv[0], X_OK) == ERROR)
		puterr_exit(argv[0], strerror(errno));
	if (is_directory(argv[0]))
		puterr_exit(argv[0], "is a directory");
	if (execve(argv[0], argv, env->envp) == ERROR)
		puterr_exit(argv[0], strerror(errno));
}

char	*get_path_value(char *const argv[], t_env *env)
{
	char	*value;

	value = search_env("PATH", env);
	if (value == NULL)
		puterr_exit(argv[0], "command not found");
	return (value);
}

void	search_path(char *const argv[], t_env *env)
{
	char	*dir_set;
	char	file_path[PATH_MAX];
	char	*dir;

	dir_set = get_path_value(argv, env);
	dir = ft_strtok(dir_set, ":");
	while (dir)
	{
		ft_strlcpy(file_path, dir, PATH_MAX);
		ft_strlcat(file_path, "/", PATH_MAX);
		ft_strlcat(file_path, argv[0], PATH_MAX);
		if (access(file_path, X_OK) == 0)
		{
			if (execve(file_path, argv, env->envp) == ERROR)
				puterr_exit(file_path, strerror(errno));
		}
		else if (errno != ENOENT)
			puterr_exit(argv[0], strerror(errno));
		dir = ft_strtok(NULL, ":");
	}
	puterr_exit(argv[0], "command not found");
}