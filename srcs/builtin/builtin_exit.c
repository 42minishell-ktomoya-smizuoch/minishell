/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smizuoch <smizuoch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 09:39:54 by smizuoch          #+#    #+#             */
/*   Updated: 2023/09/19 08:46:37 by smizuoch         ###   ########.fr       */
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

int	builtin_exit(char **argv)
{
	long	ret;
	char	*str;
	char	*arg;

	if (argv[1] == NULL)
	{
		write(1, "exit\n", 5);
		exit(SUCCESS);
	}
	errno = 0;
	arg = argv[1];
	ret = ft_strtol(arg, &str, 10);
	if (argv[2] && errno == 0)
	{
		write(2, "exit\n", 5);
		ft_putendl_fd("exit: too many arguments", 2);
		return (FAILURE);
	}
	if (is_number(arg) == 0)
	{
		if (*str == '\0' || errno == 0)
		{
			write(2, "exit\n", 5);
			exit((int)ret);
		}
	}
	write(2, "exit\n", 5);
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": numeric argument required", 2);
	exit(255);
}

// int	main(int ac, char **av)
// {
// 	(void)ac;
// 	builtin_exit(av);
// 	return (0);
// }