/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smizuoch <smizuoch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 09:39:54 by smizuoch          #+#    #+#             */
/*   Updated: 2023/11/11 14:37:14 by smizuoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"

static bool	is_number(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (true);
		str++;
	}
	return (false);
}

int	builtin_exit(char **argv, t_env *env)
{
	long	ret;
	char	*str;

	if (argv[1] == NULL)
	{
		if (env->pipe_fd != 1)
			write(1, "exit\n", 5);
		exit(SUCCESS);
	}
	errno = 0;
	ret = ft_strtol(argv[1], &str, 10);
	if (argv[2] && errno == 0)
	{
		ft_putendl_fd("exit\nexit: too many arguments", STDERR_FILENO);
		return (FAILURE);
	}
	if (is_number(argv[1]) == 0)
	{
		if (*str == '\0' || errno == 0)
		{
			write(STDERR_FILENO, "exit\n", 5);
			exit((int)ret);
		}
	}
	if (ret != 0 || errno == 0)
	{
		if (env->pipe_fd != 1)
			write(STDERR_FILENO, "exit\n", 5);
		exit((int)ret);
	}
	ft_putstr_fd("exit\nexit: ", STDERR_FILENO);
	ft_putstr_fd(argv[1], STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	exit(255);
}

// int	main(int ac, char **av)
// {
// 	(void)ac;
// 	builtin_exit(av);
// 	return (0);
// }