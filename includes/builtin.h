/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smizuoch <smizuoch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 12:37:10 by smizuoch          #+#    #+#             */
/*   Updated: 2023/10/03 14:59:21 by smizuoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <libc.h>
# include "libft.h"
# include "expansion.h"

int	builtin_echo(char **argv);
int builtin_cd(char **argv, t_env *env);
int builtin_pwd(char **argv);
int	builtin_export(char **argv, t_env *env);
int	builtin_unset(char **argv, t_env *env);
int	builtin_env(char **argv, t_env *env);
int builtin_exit(char **argv);

# endif
