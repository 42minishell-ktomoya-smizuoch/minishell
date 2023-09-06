/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smizuoch <smizuoch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:09:46 by smizuoch          #+#    #+#             */
/*   Updated: 2023/09/05 10:06:30 by smizuoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"

int	builtin_echo(char **argv)
{
	bool	option_n;
	bool	first_arg;
	size_t	i;

	i = 1;
	first_arg = true;
	if (argv[1] && ft_strcmp(argv[1], "-n") == 0)
	{
		option_n = true;
		i++;
	}
	else
		option_n = false;
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
