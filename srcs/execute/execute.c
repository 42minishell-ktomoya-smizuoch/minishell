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

#include "../../includes/minishell.h"
#include "../../includes/parser.h"
#include "../../includes/execute.h"

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

//int	execute(t_node *ast, t_env *env)
//{
//	if (ast->kind == NODE_ARGUMENT)
//		return (execute_simple_command(ast->))
//}

//int	main(int argc, char **argv, char **envp)
//{
//	const char	*line;
//	t_token		*token;
//	char		**args;
//	t_env		env;
//	t_node		*ast;
//
//	(void)argv;
//	if (argc != 1)
//		return (FAILURE);
//	env.head = NULL;
//	if (env_init(&env, envp) != 0)
//		return (FAILURE);
//	while (1)
//	{
//		line = readline("minishell$ ");
//		if (*line)
//			add_history(line);
//		else
//			continue ;
//		env.envp = env_to_envp(&env);
//		token = lexer(line);
//		ast = parser(token);
//		print_ast(ast);
//		args =
//		execute_simple_command(args, &env);
//		free_env_to_envp(env.envp);
//		free((void *)line);
//	}
//	return (0);
//}

int	main(int argc, char **argv, char **envp)
{
	const char	*line;
	t_token		*token;
	char		**args;
	t_env		env;

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
		args = malloc_token(token);
		execute_simple_command(args, &env);
		free_env_to_envp(env.envp);
		free((void *)line);
	}
	return (0);
}
