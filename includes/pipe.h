/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smizuoch <smizuoch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:04:48 by smizuoch          #+#    #+#             */
/*   Updated: 2023/11/22 15:28:56 by smizuoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

# include"libft.h"
# include "expansion.h"
# include "parser.h"
# include "execute.h"
# include "minishell.h"
# include<libc.h>

typedef struct s_pipenode
{
	int					fd[2];
	pid_t				pid;
	struct s_pipenode	*next;
	struct s_pipenode	*prev;
}	t_pipenode;

typedef struct s_pipe
{
	struct s_pipenode	*top;
	int					save_fd;
}	t_pipe;

#endif