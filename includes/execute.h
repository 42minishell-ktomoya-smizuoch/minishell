/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 19:00:33 by kudoutomoya       #+#    #+#             */
/*   Updated: 2023/11/09 11:15:46 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "libft.h"
# include "expansion.h"
# include "builtin.h"
# include "lexer.h"
# include <sys/types.h>
# include <sys/wait.h>

int		execute(t_node *ast, t_env *env);
int		execute_simple_command(char *const argv[], t_env *env);
void	puterr(const char *input, const char *msg);
void	puterr_exit(const char *input, const char *msg, int exit_status);
void	putsyserr_exit(const char *syscall_name);
bool	is_builtin(char *cmd);
bool	is_directory(char *path);
void	execute_abspath(char *const argv[], t_env *env);
char	*get_path_value(char *const argv[], t_env *env);
void	search_path(char *const argv[], t_env *env);

#endif