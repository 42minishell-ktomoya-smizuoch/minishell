/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smizuoch <smizuoch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:16:43 by smizuoch          #+#    #+#             */
/*   Updated: 2023/11/07 16:22:38 by smizuoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

void	handler_exex(int signum)
{
	if (signum == SIGINT)
	{
		write (STDIN_FILENO, "\n", 1);
	}
	if (signum == SIGQUIT)
		write (STDIN_FILENO, "Quit: 3\n", 8);
}

void	handler_heardoc(int signum)
{
	(void)signum;
	close (STDIN_FILENO);
}

void	handler_sigint(int signum)
{
	(void)signum;
	rl_on_new_line();
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_redisplay();
}

int	set_signal(int mode)
{
	if (mode == 0)
	{
		signal(SIGINT, handler_sigint);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == 1)
	{
		signal(SIGINT, handler_exex);
		signal(SIGQUIT, handler_exex);
	}
	else if (mode == 2)
	{
		signal(SIGINT, handler_heardoc);
		signal(SIGQUIT, SIG_IGN);
	}
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