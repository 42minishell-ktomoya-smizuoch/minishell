/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smizuoch <smizuoch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:32:14 by smizuoch          #+#    #+#             */
/*   Updated: 2023/10/22 14:10:44 by smizuoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

# include <fcntl.h>
# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>

char	*here_document(char *limiter);
int		*redirect_input(const char *file, int *fd);
int		*redirect_output(const char *file, int *fd);
int		*redirect_append(const char *file, int *fd);
void	restore_fd(int save_fd, int stdfd);

#endif