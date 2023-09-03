/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smizuoch <smizuoch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:10:06 by smizuoch          #+#    #+#             */
/*   Updated: 2023/09/03 16:11:10 by smizuoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"

int	my_pwd(void)
{
	char	*current_directory;

	current_directory = getcwd(NULL, 0);
	if (current_directory == NULL)
	{
		perror("getcwd");
		return (FAILURE);
	}
	printf ("%s\n", current_directory);
	return (SUCCESS);
}
