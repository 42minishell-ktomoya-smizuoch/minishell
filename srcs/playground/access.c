/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:15:18 by ktomoya           #+#    #+#             */
/*   Updated: 2023/10/03 16:29:54 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char *argv[])
{
	if (argc != 2)
		exit(1);
	if (access(argv[1], R_OK) < 0)
	{
		printf("access error for %s\n", argv[1]);
		exit(1);
	}
	else
		printf("read access OK\n");
	if (open(argv[1], O_RDONLY) < 0)
	{
		printf("open error for %s\n", argv[1]);
		exit(1);
	}
	else
		printf("open for reading OK\n");
	exit(0);
}