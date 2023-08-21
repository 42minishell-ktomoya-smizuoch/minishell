/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_executable.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:37:45 by ktomoya           #+#    #+#             */
/*   Updated: 2023/08/21 19:22:20 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	launch_executable(const char *exe_path)
{
	const char	*args[] = {exe_path, NULL};

	execve(exe_path, (char *const *)args, NULL);
	perror("execve");
	exit(FAILURE);
}
