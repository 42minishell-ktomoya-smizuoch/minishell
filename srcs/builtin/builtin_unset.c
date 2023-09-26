/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smizuoch <smizuoch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:32:44 by smizuoch          #+#    #+#             */
/*   Updated: 2023/09/16 14:47:15 by smizuoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"

void	ft_shift_env(int i, char **env)
{
	while (env[i])
	{
		env[i] = env[i + 1];
		i++;
	}
}

void	ft_unsetenv(char *name, char **env)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strjoin(name, "=");
	if (!tmp)
		return ;
	while (env[i])
	{
		if (ft_strncmp(env[i], tmp, ft_strlen(tmp)) == 0
					|| ft_strcmp(env[i], name) == 0)
		{
			free(env[i]);
			env[i] = NULL;
			ft_shift_env(i, env);
			free(tmp);
			return ;
		}
		i++;
	}
	free(tmp);
	return ;
}

int	ft_getenv(char *name, char **env)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strjoin(name, "=");
	if (!tmp)
		return (0);
	while (env[i])
	{
		if (ft_strncmp(env[i], tmp, ft_strlen(tmp)) == 0
				|| ft_strcmp(env[i], name) == 0)
		{
			free(tmp);
			return (1);
		}
		i++;
	}
	free(tmp);
	return (0);
}

int	builtin_unset(char **argv, char **env)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_strchr(argv[i], '='))
		{
			ft_putstr_fd("unset: `", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			return (1);
		}
		if (ft_getenv(argv[i], env))
			ft_unsetenv(argv[i], env);
		i++;
	}
	return (0);
}
