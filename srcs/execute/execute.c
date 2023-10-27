/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 19:03:27 by kudoutomoya       #+#    #+#             */
/*   Updated: 2023/10/27 18:25:04 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/execute.h"
#include "../../includes/redirect.h"
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
	while (ast && ast->kind == NODE_ARGUMENT)
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
	
		// 引数群を抜けてリダイレクト群に移動する
		t_node	*redir = ast;
		int 	status = 0;
		int 	*fd = ft_calloc(2, sizeof(int));
		char	*file = NULL;
		int		flag = 0;

		while (redir && redir->kind == NODE_ARGUMENT)
			redir = redir->right;
		while (redir && (redir->kind == NODE_LESS || redir->kind == NODE_GREAT || redir->kind == NODE_DGREAT || redir->kind == NODE_DLESS))
		{
			if (flag == 1)
				restore_fd(fd[0], fd[1]);
			flag = 1;
			if (redir->kind == NODE_LESS)
				fd = redirect_input(redir->word, fd);
			else if (redir->kind == NODE_GREAT)
				fd = redirect_output(redir->word, fd);
			else if (redir->kind == NODE_DGREAT)
				fd = redirect_append(redir->word, fd);
			else if (redir->kind == NODE_DLESS)
			{
				file = here_document((char *)redir->word);
				flag = 2;
			}
			redir = redir->right;
		}
		if (flag == 0)
			status = execute_simple_command(args, env);
		else if (flag == 1)
		{
			status = execute_simple_command(args, env);
			restore_fd(fd[0], fd[1]);
		}
		else if (flag == 2)
		{
			// argsの最後にfileをつける
			size_t	i = 0;

			while (args[i])
				i++;
			args[i] = file;
			status = execute_simple_command(args, env);
		}
		return (status);
	}
	else if (ast->kind == NODE_PIPE)
	{
		int		pipefd[2];
		pid_t	pid1, pid2;

		if (pipe(pipefd) < 0)
			putsyserr_exit("pipe");
		char	**cmd1 = make_argument_list(ast->left);
		pid1 = fork();
		if (pid1 == 0)
		{
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[0]);
			execute_simple_command(cmd1, env);
		}

		char	**cmd2 = make_argument_list(ast->right);
		pid2 = fork();
		if (pid2 == 0)
		{
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[1]);
			execute_simple_command(cmd2, env);
		}

		int	status;
		waitpid(pid1, &status, WNOHANG);
		waitpid(pid2, &status, WNOHANG);

		close(pipefd[0]);
		close(pipefd[1]);
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
