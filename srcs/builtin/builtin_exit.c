/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smizuoch <smizuoch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 09:39:54 by smizuoch          #+#    #+#             */
/*   Updated: 2023/09/05 11:39:50 by smizuoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"

int	builtin_exit(char **argv)
{
	if (argv[1] == NULL)
		exit(ft_atoi(argv[1]));
	if (argv[2])
	{
		perror("exit");
		return (FAILURE);
	}
	exit(255);
}