/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:09:28 by smizuoch          #+#    #+#             */
/*   Updated: 2023/11/28 17:11:37 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/execute.h"

t_pipenode	*new_pipenode(t_pipe *a_pipe)
{
	t_pipenode	*new;
	t_pipenode	*tmp;

	new = malloc(sizeof(t_pipenode));
	if (new == NULL)
		exit(1);
	if (a_pipe->top == NULL)
	{
		a_pipe->top = new;
		new->prev = NULL;
		new->next = NULL;
	}
	else
	{
		tmp = a_pipe->top;
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		tmp->next = new;
		new->prev = tmp;
		new->next = NULL;
	}
	return (new);
}

void	free_pipenode(t_pipe *a_pipe)
{
	t_pipenode	*tmp;
	t_pipenode	*tmp2;

	tmp = a_pipe->top;
	while (tmp != NULL)
	{
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
}

void	pipe_child(t_node *ast, t_env *env, t_pipenode *tmp, char *tmp_file)
{
	(void)tmp_file;
	set_signal(1);
	env->pipe_fd = 1;
	dup2(tmp->fd[1], STDOUT_FILENO);
	close(tmp->fd[0]);
	close(tmp->fd[1]);
	execute_command(ast->left, env);
	// execute_pipe_command(ast->left, env, tmp_file);
	exit(0);
}

void	pipe_parent(t_pipenode	*tmp)
{
	set_signal(3);
	dup2(tmp->fd[0], STDIN_FILENO);
	close(tmp->fd[0]);
	close(tmp->fd[1]);
}
