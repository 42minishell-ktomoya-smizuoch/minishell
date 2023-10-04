/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kudoutomoya <kudoutomoya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 19:03:27 by kudoutomoya       #+#    #+#             */
/*   Updated: 2023/10/04 14:43:46 by kudoutomoya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/execute.h"

/*
 * 目標: 相対パスで検索できるようにする
 * 準目標: getenv関数について理解する
 * 準目標: /Users/kudoutomoya/.volta/binディレクトリで検索を行う
 */

int	execute_builtin(char *const argv[])
{
	int	wstatus;

	wstatus = 0;
	/* 第１引数が"echo"だったら"../builtin/builtin_echo.o"を検索する */
	if (ft_strcmp(argv[0], "echo") == 0)
	{
		wstatus = execve("../builtin/builtin_echo.o", &argv[1], NULL);
	}
	return (wstatus);
}

int	execute_command(char *const argv[], t_env *env)
{
	pid_t	pid;
	int 	status;

	/* 外部コマンドを実行する前にビルトインコマンドに一致するか確認する */
	if (ft_strcmp(argv[0], "echo") == 0)
		return (builtin_echo((char **)argv));
	else if (ft_strcmp(argv[0], "cd") == 0)
		return (builtin_cd((char **)argv, env));
	else if (ft_strcmp(argv[0], "pwd") == 0)
		return (builtin_pwd((char **)argv));
	else if (ft_strcmp(argv[0], "export") == 0)
		return (builtin_export((char **)argv, env));
	else if (ft_strcmp(argv[0], "unset") == 0)
		return (builtin_unset((char **)argv, env));
	else if (ft_strcmp(argv[0], "env") == 0)
		return (builtin_env((char **)argv, env));
	else if (ft_strcmp(argv[0], "exit") == 0)
		return (builtin_exit((char **)argv));
//	絶対パスの検索を行う
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(FAILURE);
	}
	else if (pid == 0)
	{
		// PATHのvalueを取得する
		char *path = getenv("PATH");
		char *copy = ft_strdup(path);
		char *slash;

		copy = strtok(copy, ":");
		while (copy)
		{
			slash = ft_strdup("/");
			copy = ft_strjoin(copy, slash);
			free(slash);
			copy = ft_strjoin(copy, argv[0]);
			// 実行ファイルの実行権限を確認する
			if (access(copy, X_OK) == 0)
			{
				if (execve(copy, argv, NULL) == ERROR)
				{
					printf("%s: %s\n", argv[0], strerror(errno));
					exit(FAILURE);
				}
			}
			else if (errno == ENOENT)
				;
			else
				printf("%s: %s\n", argv[0], strerror(errno));
			free(copy);
			copy = strtok(NULL, ":");
		}
		if (errno == ENOENT)
			printf("%s: command not found\n", argv[0]);
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