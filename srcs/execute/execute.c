/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 19:03:27 by kudoutomoya       #+#    #+#             */
/*   Updated: 2023/11/18 10:42:32 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/execute.h"
#include "../../includes/redirect.h"
#include "../../includes/minishell.h"
#include "../../includes/pipe.h"

void	free_matrix(char **matrix)
{
	size_t	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

size_t	count_args(t_node *ast)
{
	size_t	count;

	count = 0;
	while (ast && ast->kind != NODE_PIPE)
	{
		if (ast->kind == NODE_ARGUMENT && ast->expand_flag == SUCCESS)
			count++;
		ast = ast->right;
	}
	return (count);
}

char	**make_argument_list(t_node *ast)
{
	char	**args;
	size_t	count;
	size_t	i;

	count = count_args(ast);
	if (count == 0)
		return (NULL);
	args = (char **)ft_calloc(count + 1, sizeof(char *));
	i = 0;
	while (i < count)
	{
		if (ast->kind != NODE_ARGUMENT || ast->expand_flag == FAILURE)
		{
			ast = ast->right;
			continue ;
		}
		else if (ast->expand)
			args[i] = ft_substr(ast->expand, 0, ft_strlen(ast->expand));
		else
			args[i] = ft_substr(ast->str, 0, ast->len);
		ast = ast->right;
		i++;
	}
	return (args);
}

int	execute_command(t_node *ast, t_env *env)
{
	int		fd[4];
	char	*tmp_file;
	int		status;
	char	**args;

	ft_memset(fd, 0, 4 * sizeof(int));
	tmp_file = NULL;
	status = 0;
	if (execute_redirect(ast, fd, &tmp_file) == ERROR)
	{
		env->exit_status = 1;
		restore_stdfd(fd);
		return (ERROR);
	}
	args = make_argument_list(ast);
	if (args)
	{
		status = launch_command(args, env);
		free_matrix(args);
	}
	restore_stdfd(fd);
	ft_unlink(tmp_file);
	return (status);
}

int	execute(t_node *ast, t_env *env)
{
	int	status;

	if (expect_node(ast, NODE_PIPE))
		pipe_cmd(ast, env);
	else
	{
		status = execute_command(ast, env);
		if (g_signal == 2)
			g_signal = 0;
		return (status);
	}
	return (SUCCESS);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	const char	*line;
// 	t_token		*token;
// 	t_env		env;
// 	t_node		*ast;

// 	(void)argv;
// 	if (argc != 1)
// 		return (FAILURE);
// 	env.head = NULL;
// 	if (env_init(&env, envp) != 0)
// 		return (FAILURE);
// 	while (1)
// 	{
// 		set_signal(0);
// 		line = readline("minishell$ ");
// 		if (!line)
// 		{
// 			write(1, "exit\n", 5);
// 			exit(0);
// 		}
// 		else if (*line)
// 			add_history(line);
// 		else
// 			continue ;
// 		env.envp = env_to_envp(&env);
// 		token = lexer(line);
// 		if (!token)
// 		{
// 			free((void *)line);
// 			continue ;
// 		}
// 		ast = parser(token);
// 		if (!ast)
// 		{
// 			free((void *)line);
// 			continue ;
// 		}
// 		ast = expand(ast, &env);
// 		execute(ast, &env);
// 		free_env_to_envp(env.envp);
// 		free((void *)line);
// 	}
// 	return (0);
// }
