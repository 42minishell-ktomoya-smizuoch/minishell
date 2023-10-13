/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smizuoch <smizuoch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 09:39:54 by smizuoch          #+#    #+#             */
/*   Updated: 2023/10/13 14:36:19 by smizuoch         ###   ########.fr       */
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

	if (argv[1] == NULL)
	{
		write(1, "exit\n", 5);
		exit(SUCCESS);
	}
	errno = 0;
	ret = ft_strtol(argv[1], &str, 10);
	if (argv[2] && errno == 0)
	{
		printf ("exit\nexit: too many arguments\n");
		return (FAILURE);
	}
	if (is_number(argv[1]) == 0)
	{
		if (*str == '\0' || errno == 0)
		{
			write(2, "exit\n", 5);
			exit((int)ret);
		}
	}
	printf ("exit\nexit: %s", argv[1]);
	printf (": numeric argument required\n");
	exit(255);
}

// int	main(int ac, char **av)
// {
// 	(void)ac;
// 	builtin_exit(av);
// 	return (0);
// }