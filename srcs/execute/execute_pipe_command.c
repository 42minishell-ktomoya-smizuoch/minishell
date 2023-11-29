/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:10:47 by ktomoya           #+#    #+#             */
/*   Updated: 2023/11/29 10:24:47 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/execute.h"

// size_t	count_tmpfile(t_node *nd, size_t count)
// {
// 	if (!nd)
// 		return (count);
// 	if (expect_node(nd, NODE_PIPE))
// 	{
// 		count = count_tmpfile(nd->left, count);
// 		return (count_tmpfile(nd->right, count));
// 	}
// 	if (expect_node(nd, NODE_DLESS))
// 		count++;
// 	return (count_tmpfile(nd->right, count));
// }

// int	make_tmpfile_list(t_node *nd, char ***tmp_file)
// {
// 	size_t	count;

// 	count = count_tmpfile(nd, 0);
// 	if (count == 0)
// 	{
// 		tmp_file = NULL;
// 		return (SUCCESS);
// 	}
// 	*tmp_file = ft_calloc(count + 1, sizeof(char *));
// 	if (*tmp_file == NULL)
// 		return (ERROR);
// 	// tmp_fileの二次元配列をsrch_here_exec関数に渡す
// 	if (srch_here_exec(nd, tmp_file) == ERROR)
// 	{
// 		return (ERROR);
// 	}
// 	return (SUCCESS);
// }

// int	srch_here_exec(t_node *nd, char ***tmp_file)
// {
// 	char	*eof;

// 	eof = NULL;
// 	if (!nd)
// 		return (SUCCESS);
// 	if (expect_node(nd, NODE_PIPE))
// 	{
// 		if (srch_here_exec(nd->left, tmp_file) == ERROR)
// 			return (ERROR);
// 		return (srch_here_exec(nd->right, tmp_file));
// 	}
// 	if (expect_node(nd, NODE_DLESS))
// 	{
// 		if (parse_file(nd, &eof) == ERROR)
// 			return (ERROR);
// 		printf("1: %p\n", tmp_file[0][0]);
// 		tmp_file[0][0] = here_document(eof);
// 		(**tmp_file)++;
// 		printf("2: %p\n", **tmp_file);
// 		free(eof);
// 		if (g_signal == 2)
// 			return (ERROR);
// 	}
// 	return (srch_here_exec(nd->right, tmp_file));
// }

// int	srch_here_exec(t_node *nd, char ***tmp_file)
// {
// 	char	*eof;

// 	eof = NULL;
// 	if (!nd)
// 		return (SUCCESS);
// 	if (expect_node(nd, NODE_PIPE))
// 	{
// 		if (srch_here_exec(nd->left, tmp_file) == ERROR)
// 			return (ERROR);
// 		return (srch_here_exec(nd->right, tmp_file));
// 	}
// 	if (expect_node(nd, NODE_DLESS))
// 	{
// 		if (parse_file(nd, &eof) == ERROR)
// 			return (ERROR);
// 		printf("1: %p\n", tmp_file[0][0]);
// 		tmp_file[0][0] = here_document(eof);
// 		(**tmp_file)++;
// 		printf("2: %p\n", **tmp_file);
// 		free(eof);
// 		if (g_signal == 2)
// 			return (ERROR);
// 	}
// 	return (srch_here_exec(nd->right, tmp_file));
// }

// int	srch_here_exec(t_node *nd, char **tmp_file)
// {
// 	char	*here_end;

// 	here_end = NULL;
// 	if (!nd)
// 		return (SUCCESS);
// 	if (expect_node(nd, NODE_PIPE))
// 	{
// 		if (srch_here_exec(nd->left, tmp_file) == ERROR)
// 			return (ERROR);
// 		if (srch_here_exec(nd->right, tmp_file) == ERROR)
// 			return (ERROR);
// 		return (SUCCESS);
// 	}
// 	if (expect_node(nd, NODE_DLESS))
// 	{
// 		ft_unlink(*tmp_file);
// 		if (parse_file(nd, &here_end) == ERROR)
// 			return (ERROR);
// 		*tmp_file = here_document(here_end);
// 		free(here_end);
// 		if (g_signal == 2)
// 			return (ERROR);
// 	}
// 	return (srch_here_exec(nd->right, tmp_file));
// }

int	exec_pipe_heredocument(int fd[2], char *tmp_file, int *heredoc_flag)
{
	if (fd[0] != fd[1])
		restore_fd(fd[0], fd[1]);
	if (redirect_input(tmp_file, fd) == ERROR)
		return (ERROR);
	*heredoc_flag = 1;
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
		else if ((nd->kind == NODE_DLESS && heredoc_flag == 0)
			&& exec_pipe_heredocument(fd, tmp_file, &heredoc_flag) == ERROR)
			return (free_retint(file, ERROR));
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
