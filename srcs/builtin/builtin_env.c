/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smizuoch <smizuoch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:33:05 by smizuoch          #+#    #+#             */
/*   Updated: 2023/09/16 17:34:54 by smizuoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"

static bool	check_env(char *env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (env[i] == '=')
			return (true);
		i++;
	}
	return (false);	
}

int	builtin_env(char **argv, char **env)
{
	int		i;
	char	*tmp;

	(void)argv;
	i = 0;
	tmp = getenv("_");
	if (!tmp)
		return (FAILURE);
	while (env[i])
	{
		if (check_env(env[i]) == true)
			ft_putendl_fd(env[i], STDOUT_FILENO);
		i++;
	}
	ft_putstr_fd("_=", STDOUT_FILENO);
	ft_putendl_fd(tmp, STDOUT_FILENO);
	return (SUCCESS);
}

// int	main (int argc, char **argv, char **env)
// {
// 	(void)argc;
// 	(void)argv;
// 	builtin_env(argv, env);
// 	return (0);
// }
