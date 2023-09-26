/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smizuoch <smizuoch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:32:22 by smizuoch          #+#    #+#             */
/*   Updated: 2023/09/16 17:53:16 by smizuoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"

static void	ft_setenv(char *name, char **env)
{
	int		i;
	char	*tmp;
	char 	new_env[PATH_MAX];

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], tmp, ft_strlen(tmp)) == 0)
		{
			free(env[i]);
			env[i] = ft_strdup(name);
			free(tmp);
			return ;
		}
		i++;
	}
	env[i] = ft_strdup(name);
	free(tmp);
	return ;
}

static bool	env_check_alpha(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (false);
	while (str[i])
	{
		if (ft_isalpha(str[i]) == false)
			return (false);
		i++;
	}
	return (true);
}

static int	put_env(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return (FAILURE);
	while (env[i])
	{
		ft_putendl_fd(env[i], STDOUT_FILENO);
		i++;
	}
	return (SUCCESS);
}

int	builtin_export(char **argv, char **env)
{
	int	i;
	int	j;
	int	status;

	i = 0;
	j = 0;
	status = SUCCESS;
	if (argv[1] == NULL)
		return (put_env(env));
	while (argv[i])
	{
		if (env_check_alpha(argv[i]) == false)
		{
			ft_putstr_fd("export: `", STDERR_FILENO);
			ft_putstr_fd(argv[i], STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			status = FAILURE;
		}
		else
		{
			ft_setenv(argv[i], env);
		}
	}
	return (status);
}
