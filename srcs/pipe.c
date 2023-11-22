/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smizuoch <smizuoch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:09:28 by smizuoch          #+#    #+#             */
/*   Updated: 2023/11/22 13:33:22 by smizuoch         ###   ########.fr       */
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

// int	execute_pipe_command(t_node *ast, t_env *env, char *tmp_file)

int	srch_here_exec(t_node *nd, t_env *env, char **tmp_file)
{
	char	*here_end;

	here_end = NULL;
	if (!nd)
		return (SUCCESS);
	if (expect_node(nd, NODE_PIPE))
	{
		if (srch_here_exec(nd->left, env, tmp_file) == ERROR)
			return (ERROR);
		if (srch_here_exec(nd->right, env, tmp_file) == ERROR)
			return (ERROR);
		return (SUCCESS);
	}
	if (expect_node(nd, NODE_DLESS))
	{
		ft_unlink(*tmp_file);
		if (parse_file(nd, &here_end) == ERROR)
			return (ERROR);
		*tmp_file = here_document(here_end);
		if (g_signal == 2)
		{
			free(here_end);
			return (ERROR);
		}
		free(here_end);
	}
	return (srch_here_exec(nd->right, env, tmp_file));
}

int	parse_redirect_file(t_node *nd, char **file)
{
	if (nd->expand_flag == FAILURE
		&& ft_memchr(nd->str, '$', nd->len)
		&& nd->kind != NODE_DLESS)
	{
		puterr_len(nd->str, nd->len, "ambiguous redirect");
		return (ERROR);
	}
	else if (nd->expand_flag == FAILURE)
	{
		*file = NULL;
		return (FAILURE);
	}
	else if (nd->expand)
		*file = ft_substr(nd->expand, 0, ft_strlen(nd->expand));
	else
		*file = ft_substr(nd->str, 0, nd->len);
	if (!*file)
		return (putsyserr_retint("malloc", ERROR));
	return (SUCCESS);
}

int	exec_pipe_redirect(t_node *nd, int fd[4], char *tmp_file)
{
	char	*file;
	int		heredoc_flag;

	heredoc_flag = 0;
	while (expect_command(nd))
	{
		if (consume_right(&nd, NODE_ARGUMENT))
			continue ;
		if (parse_file(nd, &file) == ERROR)
			return (ERROR);
		if (nd->kind == NODE_LESS && redirect_input(file, fd) == ERROR)
			return (free_retint(file, ERROR));
		else if (nd->kind == NODE_GREAT && redirect_output(file, fd) == ERROR)
			return (free_retint(file, ERROR));
		else if (nd->kind == NODE_DGREAT && redirect_append(file, fd) == ERROR)
			return (free_retint(file, ERROR));
		else if (nd->kind == NODE_DLESS && heredoc_flag == 0)
		{
			if (fd[0] != fd[1])
				restore_fd(fd[0], fd[1]);
			if (redirect_input(tmp_file, fd) == ERROR)
				return (ERROR);
			heredoc_flag = 1;
		}
		free(file);
		nd = nd->right;
	}
	return (SUCCESS);
}

int	execute_pipe_command(t_node *ast, t_env *env, char *tmp_file)
{
	int		fd[4];
	int		status;
	char	**args;

	ft_memset(fd, 0, 4 * sizeof(int));
	status = 0;
	if (exec_pipe_redirect(ast, fd, tmp_file) == ERROR)
	{
		env->exit_status = 1;
		restore_stdfd(fd);
		return (1);
	}
	args = make_argument_list(ast, env);
	if (args)
	{
		status = launch_command(args, env);
		free_matrix(args);
	}
	restore_stdfd(fd);
	return (status);
}

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
