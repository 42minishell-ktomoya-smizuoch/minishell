/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smizuoch <smizuoch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:40:39 by smizuoch          #+#    #+#             */
/*   Updated: 2023/09/03 16:40:45 by smizuoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"

int	builtin_cd(char *arg)
{
	if (!arg)
		return (1);
	if (chdir(arg) != 0)
	{
		perror ("chdir");
		return (FAILURE);
	}
	return (SUCCESS);
}
