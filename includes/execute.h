/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kudoutomoya <kudoutomoya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 19:00:33 by kudoutomoya       #+#    #+#             */
/*   Updated: 2023/09/19 19:01:17 by kudoutomoya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "libft.h"
# include <sys/types.h>
# include <sys/wait.h>

int	execute_command(char *const argv[]);

#endif