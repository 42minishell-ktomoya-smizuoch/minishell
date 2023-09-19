/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smizuoch <smizuoch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:40:39 by smizuoch          #+#    #+#             */
/*   Updated: 2023/09/19 18:32:02 by smizuoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"

int	builtin_cd(char **argv, char **env)
{
	char	*oldpwd;
	
	if (!argv[1] || ft_strcmp(argv[1], "~") == 0)
	{
		if (chdir(getenv("HOME")) != 0)
		{
			perror ("chdir");
			free(oldpwd);
			return (FAILURE);
		}
	}
	oldpwd = getcwd(NULL, 0);
	if (chdir(argv[1]) != 0)
	{
		perror ("chdir");
		free(oldpwd);
		return (FAILURE);
	}
	while (*env)
	{
		if (ft_strcmp(*env, "OLDPWD") == 0 || ft_strncmp(*env, "OLDPWD=", 7) == 0)
		{
			free(*env);
			*env = ft_strjoin("OLDPWD=", oldpwd);
			break ;
		}
		env++;
	}
	while (*env)
	{
		if (ft_strcmp(*env, "PWD") == 0 || ft_strncmp(*env, "PWD=", 4) == 0)
		{
			free(*env);
			*env = ft_strjoin("PWD=", argv[1]);
			break ;
		}
		env++;
	}
	free(oldpwd);
	printf("%s\n", getenv("PWD"));
	return (SUCCESS);
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	builtin_cd(argv, env);
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
	printf("%s\n", getenv("PWD"));
	return (0);
}
