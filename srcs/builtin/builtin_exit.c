/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smizuoch <smizuoch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 09:39:54 by smizuoch          #+#    #+#             */
/*   Updated: 2023/11/24 18:25:01 by smizuoch         ###   ########.fr       */
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

void	put_exit_m(long ret, char **argv, t_env *env, int mode)
{
	if (mode == 1)
	{
		if (env->pipe_fd != 1)
			write(1, "exit\n", 5);
		exit(env->exit_status);
	}
	if (mode == 2)
	{
		if (ft_strncmp("-9223372036854775808\0", argv[1], 22) == 0)
		{
			write(1, "exit\n", 5);
			exit(0);
		}
		ft_putstr_fd("exit\nexit: ", STDERR_FILENO);
		ft_putstr_fd(argv[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		exit(255);
	}
	if (mode == 3)
	{
		if (env->pipe_fd != 1)
			write(STDERR_FILENO, "exit\n", 5);
		exit((int)ret);
	}
}

int	builtin_exit(char **argv, t_env *env)
{
	long	ret;
	char	*str;

	ret = 0;
	if (argv[1] == NULL)
		put_exit_m(ret, argv, env, 1);
	errno = 0;
	ret = ft_strtol(argv[1], &str, 10);
	if (argv[2] && errno == 0)
	{
		ft_putendl_fd("exit\nexit: too many arguments", STDERR_FILENO);
		return (FAILURE);
	}
	if (errno != 0)
		put_exit_m(ret, argv, env, 2);
	if (is_number(argv[1]) == 0)
	{
		if (*str == '\0' || errno == 0)
			put_exit_m(ret, argv, env, 3);
	}
	if (ret != 0 || errno == 0)
		put_exit_m(ret, argv, env, 3);
	put_exit_m(ret, argv, env, 2);
	exit(255);
}

// int	main(int ac, char **av)
// {
// 	(void)ac;
// 	builtin_exit(av);
// 	return (0);
// }