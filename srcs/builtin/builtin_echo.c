/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smizuoch <smizuoch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:09:46 by smizuoch          #+#    #+#             */
/*   Updated: 2023/09/08 13:01:21 by smizuoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"

bool	n_check(char **argv, size_t *i)
{
	int	j;

	j = 1;
	if (argv[*i][0] != '-')
		return (false);
	while (argv[*i][j])
	{
		if (argv[*i][j] != 'n')
			return (false);
		j++;
	}
	return (true);
}

int	builtin_echo(char **argv)
{
	bool	option_n;
	bool	first_arg;
	size_t	i;

	i = 1;
	first_arg = true;
	option_n = false;
	while (argv[i] && n_check(argv, &i) == true)
	{
		option_n = true;
		i++;
	}
	while (argv[i])
	{
		if (!first_arg)
			write(1, " ", 1);
		write(1, argv[i], ft_strlen(argv[i]));
		first_arg = false;
		i++;
	}
	if (!option_n)
		write(1, "\n", 1);
	return (SUCCESS);
}

// int	main(int ac, char **av)
// {
// 	(void)ac;
// 	builtin_echo(av);
// 	return 0;
// }
