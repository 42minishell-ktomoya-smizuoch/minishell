/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smizuoch <smizuoch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 13:00:27 by smizuoch          #+#    #+#             */
/*   Updated: 2023/09/05 11:39:31 by smizuoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"

int	builtin_list(char *command, char **arg)
{
	if (ft_strcmp(command, "echo") == 0)
		return (builtin_echo(arg));
	else if (ft_strcmp(command, "cd") == 0)
		return (builtin_cd(arg));
	else if (ft_strcmp(command, "pwd") == 0)
		return (my_pwd(arg));
	// else if (ft_strcmp(command, "export") == 0)
	// 	return (builtin_export());
	// else if (ft_strcmp(command, "unset") == 0)
	// 	return (builtin_unset());
	// else if (ft_strcmp(command, "env") == 0)
	// 	return (builtin_env());
	// else if (ft_strcmp(command, "exit") == 0)
	// 	return (builtin_exit());
	return (0);
}

// int	main(int argc, char **argv)
// {
// 	if (argc < 2)
// 		return (FAILURE);
// 	return (builtin_list(argv[1], argv[2]));
// }
