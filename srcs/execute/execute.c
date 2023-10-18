/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kudoutomoya <kudoutomoya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 19:03:27 by kudoutomoya       #+#    #+#             */
/*   Updated: 2023/10/14 19:03:52 by kudoutomoya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/execute.h"
#include "../../includes/minishell.h"

/*
 * 目標: 単純なコマンドを出力できるようにする
 * 準目標: 構文木にあるコマンドの引数群をmallocする
 */

static int	execute_builtin(char *cmds[], t_env *env)
{
	if (ft_strcmp(cmds[0], "echo") == 0)
		return (builtin_echo(cmds));
	else if (ft_strcmp(cmds[0], "cd") == 0)
		return (builtin_cd(cmds, env));
	else if (ft_strcmp(cmds[0], "pwd") == 0)
		return (builtin_pwd(cmds));
	else if (ft_strcmp(cmds[0], "export") == 0)
		return (builtin_export(cmds, env));
	else if (ft_strcmp(cmds[0], "unset") == 0)
		return (builtin_unset(cmds, env));
	else if (ft_strcmp(cmds[0], "env") == 0)
		return (builtin_env(cmds, env));
	else
		return (builtin_exit(cmds));
}

static int	execute_executable(char *const argv[], t_env *env)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid < 0)
		putsyserr_exit("fork");
	else if (pid == 0)
	{
		if (ft_strchr(argv[0], '/'))
			execute_abspath(argv, env);
		else
			search_path(argv, env);
	}
	else
	{
		if (wait(&status) != pid)
			putsyserr_exit("wait");
	}
	return (status);
}

int	execute_simple_command(char *const argv[], t_env *env)
{
	if (is_builtin(argv[0]))
		return (execute_builtin((char **)argv, env));
	else
		return (execute_executable(argv, env));
}

size_t	count_args(t_node *ast)
{
	size_t	count;

	count = 0;
	while (ast)
	{
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
	args = (char **)ft_calloc(count + 1, sizeof(char *));
	i = 0;
	while (i < count)
	{
		args[i] = (char *)ast->word;
		ast = ast->right;
		i++;
	}
	return (args);
}

int	execute(t_node *ast, t_env *env)
{
	char	**args;

	args = NULL;
	if (ast->kind == NODE_ARGUMENT)
	{
		args = make_argument_list(ast); // Todo: 構文木をfreeする
		return (execute_simple_command(args, env));
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	const char	*line;
	t_token		*token;
	t_env		env;
	t_node		*ast;

	(void)argv;
	if (argc != 1)
		return (FAILURE);
	env.head = NULL;
	if (env_init(&env, envp) != 0)
		return (FAILURE);
	while (1)
	{
		line = readline("minishell$ ");
		if (*line)
			add_history(line);
		else
			continue ;
		env.envp = env_to_envp(&env);
		token = lexer(line);
		ast = parser(token);
		execute(ast, &env);
		free_env_to_envp(env.envp);
		free((void *)line);
	}
	return (0);
}
