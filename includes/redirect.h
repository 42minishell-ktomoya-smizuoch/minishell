/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:32:14 by smizuoch          #+#    #+#             */
/*   Updated: 2023/11/14 16:08:07 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

# include <fcntl.h>
# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>

char	*here_document(char *limiter);
int		redirect_input(const char *file, int fd[4]);
int		redirect_output(const char *file, int fd[4]);
int		redirect_append(const char *file, int fd[4]);
void	restore_fd(int save_fd, int stdfd);

#endif