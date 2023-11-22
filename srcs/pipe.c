/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smizuoch <smizuoch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:09:28 by smizuoch          #+#    #+#             */
/*   Updated: 2023/11/22 14:21:27 by smizuoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/execute.h"

int	pipe_cmd(t_node *ast, t_env *env)
{
	int			status;
	t_pipe		a_pipe;
	t_pipenode	*tmp;
	char		*tmp_file;

	a_pipe.top = NULL;
	a_pipe.save_fd = dup(0);
	tmp_file = NULL;
	while (ast->kind == NODE_PIPE)
	{
		set_signal(1);
		tmp = new_pipenode(&a_pipe);
		if (pipe(tmp->fd) < 0)
			putsyserr_exit("pipe");
		if (srch_here_exec(ast, env, &tmp_file) == ERROR)
			break ;
		if ((tmp->pid = fork()) == 0)
		{
			set_signal(1);
			env->pipe_fd = 1;
			dup2(tmp->fd[1], STDOUT_FILENO);
			close(tmp->fd[0]);
			close(tmp->fd[1]);
			execute_pipe_command(ast->left, env, tmp_file);
			exit(0);
		}
		else if (tmp->pid == -1)
		{
			perror("fork");
			break ;
		}
		set_signal(3);
		dup2(tmp->fd[0], STDIN_FILENO);
		close(tmp->fd[0]);
		close(tmp->fd[1]);
		ast = ast->right;
		if (ast->kind != NODE_PIPE)
		{
			tmp = new_pipenode(&a_pipe);
			if ((tmp->pid = fork()) == 0)
			{
				set_signal(1);
				env->pipe_fd = 1;
				status = execute_pipe_command(ast, env, tmp_file);
				exit(status);
			}
			else if (tmp->pid == -1)
			{
				perror("fork");
				break ;
			}
			set_signal(3);
			break ;
		}
	}
	tmp = a_pipe.top;
	dup2(a_pipe.save_fd, 0);
	while (tmp->next)
	{
		waitpid(tmp->pid, &status, 0);
		if (WIFSIGNALED(status))
			write (1, "\n", 1);
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
		write (1, "\n", 1);
		env->exit_status = WTERMSIG(status) + 128;
	}
	tmp = a_pipe.top;
	free_pipenode(&a_pipe);
	return (0);
}
