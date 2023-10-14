/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 19:03:27 by kudoutomoya       #+#    #+#             */
/*   Updated: 2023/10/13 19:40:18 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/execute.h"

/*
 * 目標: envpをexecveに渡す
 */

void	puterr_exit(const char *input, const char *msg)
{
	ft_putstr_fd(input, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	exit(FAILURE);
}

void	putsyserr_exit(const char *syscall_name)
{
	perror(syscall_name);
	exit(FAILURE);
}

bool	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0)
		return (true);
	return (false);
}

bool	is_directory(char *path)
{
	struct stat	buf;

	if (stat(path, &buf) == ERROR)
		putsyserr_exit("stat");
	if (S_ISDIR(buf.st_mode))
		return (true);
	return (false);
}

int	execute_builtin(char *cmds[], t_env *env)
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

void	execute_path(char *const argv[], t_env *env)
{
	if (access(argv[0], X_OK) == ERROR)
		puterr_exit(argv[0], strerror(errno));
	if (execve(argv[0], argv, env->envp) == ERROR)
		putsyserr_exit("execve");
}

void	execute_abspath(char *const argv[], t_env *env)
{
	if (access(argv[0], X_OK) == ERROR)
		puterr_exit(argv[0], strerror(errno));
	if (is_directory(argv[0]))
		puterr_exit(argv[0], "is a directory");
	if (execve(argv[0], argv, env->envp) == ERROR)
		putsyserr_exit("execve");
}

char	*get_path_value(char *const argv[], t_env *env)
{
	char	*value;

	value = search_env("PATH", env);
	if (value == NULL)
		puterr_exit(argv[0], "command not found");
	return (value);
}

void	search_path(char *const argv[], t_env *env)
{
	char	*dir_set;
	char	file_path[PATH_MAX];
	char	*dir;

	dir_set = get_path_value(argv, env);
	dir = ft_strtok(dir_set, ":");
	while (dir)
	{
		ft_strlcpy(file_path, dir, PATH_MAX);
		ft_strlcat(file_path, "/", PATH_MAX);
		ft_strlcat(file_path, argv[0], PATH_MAX);
		if (access(file_path, X_OK) == 0)
		{
			if (execve(file_path, argv, env->envp) == ERROR)
				puterr_exit(file_path, strerror(errno));
		}
		else if (errno != ENOENT)
			puterr_exit(argv[0], strerror(errno));
		dir = ft_strtok(NULL, ":");
	}
	puterr_exit(argv[0], "command not found");
}

int	execute_executable(char *const argv[], t_env *env)
{
	pid_t	pid;
	int		status;

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
	return (0);
}

int	execute_command(char *const argv[], t_env *env)
{
	if (is_builtin(argv[0]))
		return (execute_builtin((char **)argv, env));
	else
		return (execute_executable(argv, env));
}

size_t	count_token(t_token *tok)
{
	t_token	*cur;
	size_t	count;

	cur = tok;
	count = 0;
	while (cur->type != TYPE_EOF)
	{
		count++;
		cur = cur->next;
	}
	return (count);
}

char	**malloc_token(t_token *tok)
{
	t_token	*cur;
	char	**argv;
	size_t	count;
	size_t	i;

	cur = tok;
	count = count_token(tok);
	argv = ft_calloc(count + 1, sizeof(char *));
	i = 0;
	while (i < count)
	{
		argv[i] = ft_substr(cur->str, 0, cur->len);
		if (argv[i] == NULL)
			return (NULL);
		cur = cur->next;
		i++;
	}
	return (argv);
}

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
		execute_command(args, &env);
		free_env_to_envp(env.envp);
		free((void *)line);
	}
	return (0);
}
