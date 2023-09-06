/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smizuoch <smizuoch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:40:39 by smizuoch          #+#    #+#             */
/*   Updated: 2023/09/05 11:38:28 by smizuoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"

int	builtin_cd(char **argv)
{
	if (!argv[1])
		return (1);
	if (chdir(*argv[1]) != 0)
	{
		perror ("chdir");
		return (FAILURE);
	}
	return (SUCCESS);
}
