/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smizuoch <smizuoch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:09:28 by smizuoch          #+#    #+#             */
/*   Updated: 2023/12/01 10:15:42 by smizuoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/execute.h"

void	pipe_wait(t_env *env, t_pipenode *tmp, t_pipe *a_pipe, char *tmp_file)
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
	waitpid(tmp->pid, &status, 0);
	if (WIFEXITED(status))
	{
		env->exit_status = WEXITSTATUS(status);
		ft_unlink(tmp_file);
	}
	else if (WIFSIGNALED(status))
	{
		if (f == 1)
			write (1, "\n", 1);
		env->exit_status = WTERMSIG(status) + 128;
	}
	tmp = a_pipe->top;
	free_pipenode(a_pipe);
}

void	end_child(t_node *ast, t_env *env, t_pipenode *tmp, char *tmp_file)
{
	(void)tmp_file;
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
	char		*tmp_file;

	a_pipe.top = NULL;
	a_pipe.save_fd = dup(0);
	tmp_file = NULL;
	while (ast->kind == NODE_PIPE)
	{
		setup_signal_and_pipe(&a_pipe, &tmp);
		if (tmp->pid == 0)
			pipe_child(ast, env, tmp, tmp_file);
		else if (tmp->pid == -1 && perror_retint("fork", ERROR) == ERROR)
			break ;
		pipe_parent(tmp);
		ast = ast->right;
		if (ast->kind != NODE_PIPE)
			tmp = new_pipenode(&a_pipe);
		if (ast->kind != NODE_PIPE)
			end_child(ast, env, tmp, tmp_file);
	}
	pipe_wait(env, tmp, &a_pipe, tmp_file);
	return (0);
}
