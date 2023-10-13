/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 19:03:27 by kudoutomoya       #+#    #+#             */
/*   Updated: 2023/10/10 17:40:04 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/execute.h"

/*
 * 目標: リファクタリング
 * 準目標: ビルトインか確認する処理を追加する
 * 準目標: copyをmallocしない構造にする
 */

void	puterr_exit(const char *input, const char *msg)
{
	ft_putstr_fd(input, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	exit(FAILURE);
}

bool	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0 ||
		ft_strcmp(cmd, "cd") == 0 ||
		ft_strcmp(cmd, "pwd") == 0 ||
		ft_strcmp(cmd, "export") == 0 ||
		ft_strcmp(cmd, "unset") == 0 ||
		ft_strcmp(cmd, "env") == 0 ||
		ft_strcmp(cmd, "exit") == 0)
		return (true);
	return (false);
}

bool	is_directory(char *path)
{
	struct stat	buf;

	if (stat(path, &buf) == ERROR)
	{
		perror("stat");
		exit(FAILURE);
	}
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

void	execute_path(char *const argv[])
{
	if (access(argv[0], X_OK) == ERROR)
		puterr_exit(argv[0], strerror(errno));
	if (execve(argv[0], argv, NULL) == ERROR)
		puterr_exit(argv[0], strerror(errno));
}

void	execute_abspath(char *const argv[])
{
	if (access(argv[0], X_OK) == ERROR)
		puterr_exit(argv[0], strerror(errno));
	if (is_directory(argv[0]))
		puterr_exit(argv[0], "is a directory");
	if (execve(argv[0], argv, NULL) == ERROR)
		puterr_exit(argv[0], strerror(errno));
}

//void	search_PATH(char *const argv[], t_env *env)
//{
//	char	*path;
//	char	copy[PATH_MAX];
//
//	ft_bzero(copy, PATH_MAX);
//	path = search_env("PATH", env);
//	if (path == NULL || ft_strchr(path, '/') == NULL)
//		puterr_exit(argv[0], "command not found");
//	path = ft_strchr(path, '/');
//	copy = ft_memcpy(copy, path, ft_strlen(path));
//	copy = ft_strtok(copy, ":");
//	while (copy)
//	{
//		copy = ft_strjoin(copy, "/");
//		copy = ft_strjoin(copy, argv[0]);
//
//	}
//}

void	search_PATH(char *const argv[], t_env *env)
{
	char	*path;
	char	*copy;

	path = search_env("PATH", env);
	if (path == NULL || ft_strchr(path, '/') == NULL)
		puterr_exit(argv[0], "command not found");
	path = ft_strchr(path, '/');
	copy = ft_strdup(path);
	copy = ft_strtok(copy, ":");
	while (copy)
	{
		copy = ft_strjoin(copy, "/");
		copy = ft_strjoin(copy, argv[0]);
		if (access(copy, X_OK) == 0)
		{
			if (execve(copy, argv, NULL) == ERROR)
				puterr_exit(argv[0], strerror(errno));
		}
		else if (errno == ENOENT)
			;
		else
			puterr_exit(argv[0], strerror(errno));
		free(copy);
		copy = ft_strtok(NULL, ":");
	}
	puterr_exit(argv[0], "command not found");
}

int	execute_executable(char *const argv[], t_env *env)
{
	pid_t	pid;
	int 	status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(FAILURE);
	}
	else if (pid == 0)
	{
		if (ft_strchr(argv[0], '/'))
			execute_abspath(argv);
		else
			search_PATH(argv, env);
	}
	else
	{
		if (wait(&status) != pid)
		{
			perror("wait");
			exit(FAILURE);
		}
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
	char 		**args;
	t_env 		env;

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
		token = lexer(line);
		args = malloc_token(token);
		execute_command(args, &env);
		free((void *)line);
	}
	return (0);
}

//int	main(void)
//{
//	int		var; /* スタック上の自動変数 */
//	pid_t	pid;
//
//	var = 88;
//	if (write(STDOUT_FILENO, buf, sizeof(buf) - 1) != sizeof(buf) - 1)
//		exit(1);
//	printf("before fork\n"); /* 標準出力をフラッシュしない */
//	if ((pid = fork()) < 0)
//		exit(1);
//	else if (pid == 0) /* 子側 */
//	{
//		globvar++; /* 変数を変更する */
//		var++;
//	}
//	else
//		sleep(2); /* 親側 */
//	printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar, var);
//}