/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 10:23:53 by ktomoya           #+#    #+#             */
/*   Updated: 2023/11/18 10:25:02 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

void	restore_stdfd(int fd[4])
{
	if (fd[0] != fd[1])
		restore_fd(fd[0], fd[1]);
	if (fd[2] != fd[3])
		restore_fd(fd[2], fd[3]);
}

void	ft_unlink(char *file)
{
	if (file)
	{
		unlink(file);
		free(file);
	}
}
