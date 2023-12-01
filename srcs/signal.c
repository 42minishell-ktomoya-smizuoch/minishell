/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smizuoch <smizuoch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:16:43 by smizuoch          #+#    #+#             */
/*   Updated: 2023/12/01 10:29:38 by smizuoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

void	signal_mode_zero(struct sigaction *sa)
{
	sa->sa_handler = handler_sigint;
	sa->sa_flags = 0;
	sigaction(SIGINT, sa, NULL);
	sa->sa_handler = SIG_IGN;
	sigaction(SIGQUIT, sa, NULL);
}

void	signal_mode_one(struct sigaction *sa)
{
	sa->sa_handler = handler_exec;
	sa->sa_flags = SA_SIGINFO;
	sigaction(SIGINT, sa, NULL);
	sigaction(SIGQUIT, sa, NULL);
}

void	handler_exec_pipe(int signum)
{
	if (signum == SIGINT)
	{
		g_signal = 4;
	}
}

void	signal_mode_pipe(struct sigaction *sa)
{
	sa->sa_handler = handler_exec_pipe;
	sa->sa_flags = SA_SIGINFO;
	signal(SIGINT, handler_exec_pipe);
	sa->sa_handler = SIG_IGN;
	sigaction(SIGQUIT, sa, NULL);
}

int	set_signal(int mode)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	if (mode == 0)
		signal_mode_zero(&sa);
	else if (mode == 1)
		signal_mode_one(&sa);
	else if (mode == 2)
	{
		sa.sa_handler = handler_heardoc;
		sa.sa_flags = SA_SIGINFO;
		sigaction(SIGINT, &sa, NULL);
		sa.sa_handler = SIG_IGN;
		sigaction(SIGQUIT, &sa, NULL);
	}
	else if (mode == 3)
	{
		sa.sa_handler = SIG_IGN;
		sa.sa_flags = SA_SIGINFO;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
	}
	else if (mode == 4)
		signal_mode_pipe(&sa);
	return (0);
}

// int main()
// {
// 	char	*line;
// 	while (1)
// 	{
// 		set_signal();
// 		line = readline("minishell$ ");
// 		if (line[0] == 'a')
// 			return 0;
// 	}
// }