/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kudoutomoya <kudoutomoya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 19:03:27 by kudoutomoya       #+#    #+#             */
/*   Updated: 2023/10/01 20:16:31 by kudoutomoya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/execute.h"
#include "../../includes/builtin.h"

/*
 * 目標: ビルトインコマンドを実行する
 * 準目標: ビルトインechoを実行する
 * 準目標: ビルトインpwdを実行する
 * 準目標: ビルトインexitを実行する
 * 準目標: getenvについて理解する
 * 準目標: ビルトインcdを実行する
 */

/*
 * そもそもビルトインコマンドを実行するのにexecve関数を使う必要性を感じない
 * execve関数がいらないなら、fork関数もいらない
 * 違う、コマンドがパス扱いだった場合の挙動を一緒にしなければならない
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

int	execute_command(char *const argv[])
{
	pid_t	pid;
	int 	status;

	/* 外部コマンドを実行する前にビルトインコマンドに一致するか確認する */
	if (ft_strcmp(argv[0], "echo") == 0)
		return (builtin_echo((char **)argv));
//	else if (ft_strcmp(argv[0], "cd") == 0)
//		return (builtin_cd((char **)argv, NULL));
	else if (ft_strcmp(argv[0], "pwd") == 0)
		return (builtin_pwd((char **)argv));
//	else if (ft_strcmp(argv[0], "export") == 0)
//		return (builtin_export((char **)argv, NULL));
//	else if (ft_strcmp(argv[0], "unset") == 0)
//		return (builtin_unset((char **)argv, NULL));
//	else if (ft_strcmp(argv[0], "env") == 0)
//		return (builtin_env((char **)argv, NULL));
	else if (ft_strcmp(argv[0], "exit") == 0)
		return (builtin_exit((char **)argv));
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(FAILURE);
	}
	else if (pid == 0)
	{
		if (execve(argv[0], argv, NULL) == ERROR)
		{
			perror("execve");
			exit(FAILURE);
		}
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

int	main(int argc, char **argv)
{
	const char	*line;
	t_token		*token;
	char 		**args;

	(void)argv;
	if (argc != 1)
		return (FAILURE);
	while (1)
	{
		line = readline("minishell$ ");
		if (*line)
			add_history(line);
		token = lexer(line);
		args = malloc_token(token);
		execute_command(args);
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