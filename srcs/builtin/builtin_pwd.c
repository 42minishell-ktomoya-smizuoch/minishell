/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smizuoch <smizuoch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:10:06 by smizuoch          #+#    #+#             */
/*   Updated: 2023/09/09 15:49:46 by smizuoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"

int	builtin_pwd(char **argv)
{
	char	*current_directory;

	(void)argv;
	current_directory = getcwd(NULL, 0);
	if (current_directory == NULL)
	{
		perror("getcwd");
		return (FAILURE);
	}
	printf ("%s\n", current_directory);
	free(current_directory);
	return (SUCCESS);
}

// int	main()
// {
// 	builtin_pwd();
// }
