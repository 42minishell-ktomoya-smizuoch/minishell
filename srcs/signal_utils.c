/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smizuoch <smizuoch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:16:43 by smizuoch          #+#    #+#             */
/*   Updated: 2023/11/21 09:30:51 by smizuoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

void	check_signal(t_env *env)
{
	if (g_signal == 1 || g_signal == 2)
	{
		env->exit_status = 1;
	}
	else if (g_signal == 130)
	{
		env->exit_status = 130;
	}
	else if (g_signal == 131)
	{
		env->exit_status = 131;
	}
	g_signal = 0;
}

void	handler_exec(int signum)
{
	if (signum == SIGINT)
	{
		write (STDIN_FILENO, "\n", 1);
		g_signal = 130;
	}
	if (signum == SIGQUIT)
	{
		write (STDIN_FILENO, "Quit: 3\n", 8);
		g_signal = 131;
	}
}

void	handler_heardoc(int signum)
{
	(void)signum;
	if (signum == SIGINT)
	{
		close(0);
		g_signal = 2;
	}
}

void	handler_sigint(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		g_signal = 1;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
