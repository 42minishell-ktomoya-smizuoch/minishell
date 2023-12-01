/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smizuoch <smizuoch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:09:28 by smizuoch          #+#    #+#             */
/*   Updated: 2023/12/01 11:10:40 by smizuoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/execute.h"

void	endpid_wait(t_pipenode *end, int status, t_env *env, int f)
{
	waitpid(end->pid, &status, 0);
	if (WIFEXITED(status))
		env->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (f == 1)
			write (1, "\n", 1);
		env->exit_status = WTERMSIG(status) + 128;
	}
}

void	pipe_wait(t_env *env, t_pipenode *tmp, t_pipe *a_pipe)
{
	int	status;
	int	f;

	f = 1;
	status = 0;
	tmp = a_pipe->top;
	restore_fd(a_pipe->save_fd, 0);
	while (tmp->next)
	{
		waitpid(tmp->pid, &status, 0);
		if (WIFSIGNALED(status))
		{
			if (g_signal == 4 && f == 1)
			{
				write (1, "\n", 1);
				f = 0;
			}
			env->exit_status = WTERMSIG(status) + 128;
		}
		tmp = tmp->next;
	}
	endpid_wait(tmp, status, env, f);
	tmp = a_pipe->top;
	free_pipenode(a_pipe);
}

void	end_child(t_node *ast, t_env *env, t_pipenode *tmp)
{
	tmp->pid = fork();
	if (tmp->pid == 0)
	{
		set_signal(1);
		env->pipe_fd = 1;
		exit(execute_command(ast, env));
	}
	else if (tmp->pid == -1)
		perror("fork");
	set_signal(4);
}

void	setup_signal_and_pipe(t_pipe *a_pipe, t_pipenode **tmp)
{
	set_signal(1);
	*tmp = new_pipenode(a_pipe);
	if (pipe((*tmp)->fd) < 0)
		putsyserr_exit("pipe");
	(*tmp)->pid = fork();
}

int	pipe_cmd(t_node *ast, t_env *env)
{
	t_pipe		a_pipe;
	t_pipenode	*tmp;

	a_pipe.top = NULL;
	a_pipe.save_fd = dup(0);
	while (ast->kind == NODE_PIPE)
	{
		setup_signal_and_pipe(&a_pipe, &tmp);
		if (tmp->pid == 0)
			pipe_child(ast, env, tmp);
		else if (tmp->pid == -1 && perror_retint("fork", ERROR) == ERROR)
			break ;
		pipe_parent(tmp);
		ast = ast->right;
		if (ast->kind != NODE_PIPE)
			tmp = new_pipenode(&a_pipe);
		if (ast->kind != NODE_PIPE)
			end_child(ast, env, tmp);
	}
	pipe_wait(env, tmp, &a_pipe);
	return (0);
}
