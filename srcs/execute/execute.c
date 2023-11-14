/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 19:03:27 by kudoutomoya       #+#    #+#             */
/*   Updated: 2023/11/14 16:16:06 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/execute.h"
#include "../../includes/redirect.h"
#include "../../includes/minishell.h"
#include "../../includes/pipe.h"

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
		return (builtin_exit(cmds, env));
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
		set_signal(1);
		if (ft_strchr(argv[0], '/'))
			execute_abspath(argv, env);
		else
			search_path(argv, env);
	}
	else
	{
        set_signal(3);
        // if (wait(&status) == -1)
        if (wait(&status) != pid)
		{
			write(1, "aaaaa", 5);
            putsyserr_exit("wait");
		}
        if (WIFEXITED(status))
            env->exit_status = WEXITSTATUS(status);
        else if (WIFSIGNALED(status))
        {
            write (1, "\n", 1);
            env->exit_status = WTERMSIG(status) + 128;
        }
    }
	return (status);
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
			args[i] = ast->expand;
		else
			args[i] = ft_substr(ast->str, 0, ast->len); // Todo: mallocのfree
		ast = ast->right;
		i++;
	}
	return (args);
}


int	execute_simple_command(char *const argv[], t_env *env)
{
	if (is_builtin(argv[0]))
	{
		env->exit_status = execute_builtin((char **)argv, env);
		return (0);
	}
	else
		return (execute_executable(argv, env));
}

int	execute_redirect(t_node *ast, int fd[4], char *tmp_file)
{
	t_node	*redir;
	char	*file_here;
	int		status;

	redir = ast;
	status = 0;
	while (redir && redir->kind != NODE_PIPE)
	{
        if (redir->kind == NODE_ARGUMENT)
        {
            redir = redir->right;
            continue ;
        }
        if (redir->expand_flag == FAILURE)
        {
            file_here = ft_substr(redir->str, 0, redir->len);
            puterr(file_here, "ambiguous redirect");
            free(file_here);
            return (ERROR);
        }
        else if (redir->expand)
            file_here = redir->expand;
        else
            file_here = ft_substr(redir->str, 0, redir->len);
		if (redir->kind == NODE_LESS)
		{
			if (fd[0] != fd[1])
				restore_fd(fd[0], fd[1]);
			// fd = redirect_input(file_here, fd);
			if (redirect_input(file_here, fd) == ERROR)
			{
				free(file_here);
				return (ERROR);
			}
		}
		else if (redir->kind == NODE_GREAT)
		{
			if (fd[2] != fd[3])
				restore_fd(fd[2], fd[3]);
            // fd = redirect_output(file_here, fd);
			if (redirect_output(file_here, fd) == ERROR)
			{
				free(file_here);
				return (ERROR);
			}
		}
		else if (redir->kind == NODE_DGREAT)
		{
			// fd = redirect_append(file_here, fd);
			if (fd[2] != fd[3])
				restore_fd(fd[2], fd[3]);
			if (redirect_append(file_here, fd) == ERROR)
			{
				free(file_here);
				return (ERROR);
			}
		}
		else if (redir->kind == NODE_DLESS)
		{
			if (tmp_file)
			{
				unlink(tmp_file);
				free(tmp_file);
			}
			if (fd[0] != fd[1])
				restore_fd(fd[0], fd[1]);
			tmp_file = here_document(file_here);
			if (g_signal == 2)
				return (ERROR);
			// fd = redirect_input(tmp_file, fd);
			redirect_input(tmp_file, fd);
		}
		redir = redir->right;
	}
	return (0);
}

int execute_command(t_node *ast, t_env *env)
{
	char	**args;
	int 	fd[4];
	char 	*tmp_file;
	int 	status = 0;

    args = make_argument_list(ast);
	if (!args)
		return (ERROR);
	ft_memset(fd, 0, 4 * sizeof(int));
	tmp_file = NULL;
	if (execute_redirect(ast, fd, tmp_file) == ERROR)
	{
		env->exit_status = 1;
		if (fd[0] != fd[1])
			restore_fd(fd[0], fd[1]);
		if (fd[2] != fd[3])
			restore_fd(fd[2], fd[3]);
		return (ERROR);
	}
	status = execute_simple_command(args, env);
	if (fd[0] != fd[1])
		restore_fd(fd[0], fd[1]);
	if (fd[2] != fd[3])
		restore_fd(fd[2], fd[3]);
	if (tmp_file)
	{
		unlink(tmp_file);
		free(tmp_file);
	}
	if (g_signal == 2)
		g_signal = 0;
	return (status);
}

int	execute(t_node *ast, t_env *env)
{
	int	status;

	if (ast->kind == NODE_PIPE)
	{
		int		pipefd[2];
		pid_t	pid1, pid2;
		int	stdin_fd = dup(0);

		if (pipe(pipefd) < 0)
			putsyserr_exit("pipe");
		char	**cmd1 = make_argument_list(ast->left);
		pid1 = fork();
		if (pid1 == 0)
		{
			env->pipe_fd = 1;
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[0]);
			close(pipefd[1]);
			execute_simple_command(cmd1, env);
			exit(0);
		}
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		char	**cmd2 = make_argument_list(ast->right);
		pid2 = fork();
		if (pid2 == 0)
		{
			env->pipe_fd = 1;
			execute_simple_command(cmd2, env);
			exit(0);
		}
		int	status;
		dup2(stdin_fd, STDIN_FILENO);
		waitpid(pid1, &status, 0);
		waitpid(pid2, &status, 0);
	}
    else
    {
        status = execute_command(ast, env);
        return (status);
    }
	return (0);
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
