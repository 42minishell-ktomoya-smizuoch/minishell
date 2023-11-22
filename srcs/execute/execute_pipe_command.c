/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smizuoch <smizuoch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:10:47 by ktomoya           #+#    #+#             */
/*   Updated: 2023/11/22 14:22:13 by smizuoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/execute.h"

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
		free(here_end);
		if (g_signal == 2)
			return (ERROR);
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
