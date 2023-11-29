/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 10:38:22 by ktomoya           #+#    #+#             */
/*   Updated: 2023/11/29 16:04:37 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"
#include "../../includes/minishell.h"

static int	wait_child(pid_t pid)
{
	int	status;

	if (wait(&status) != pid)
		putsyserr_exit("wait");
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		write(1, "\n", 1);
		status = WTERMSIG(status) + 128;
	}
	return (status);
}

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
	if (pid == ERROR)
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
		status = wait_child(pid);
	}
	return (status);
}

int	launch_command(char *const argv[], t_env *env)
{
	if (is_builtin(argv[0]))
		return (execute_builtin((char **)argv, env));
	else
		return (execute_executable(argv, env));
}
