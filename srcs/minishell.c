/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smizuoch <smizuoch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:50:09 by ktomoya           #+#    #+#             */
/*   Updated: 2023/09/16 15:13:27 by smizuoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	main(int argc, char **argv)
// {
// 	if (argc < 2)
// 		return (FAILURE);
// //	display_prompt();
// 	// launch_executable((const char *)argv[1]);
// 	return (SUCCESS);
// }

static int	envp_init(char **envp)
{
	int		i;

	i = 0;
	if (!envp)
		return (FAILURE);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "_=", 2) == 0)
		{
			envp[i] = NULL;
			break ;
		}
		i++;
	}
	if (envp[i] == NULL)
	{
		envp[i] = ft_strdup("OLDPWD");
		if (!envp[i])
			return (FAILURE);
	}
	return (SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_token		*tokens;
	t_token		*current;
	const char	*line;

	(void)argv;
	envp_init(envp);
	if (argc != 1)
		return (FAILURE);
	while (1)
	{
		line = readline("minishell$ ");
		if (*line)
			add_history(line);
		tokens = lexer(line);
		current = tokens;
		while (current != NULL)
		{
			printf("Token: %s, Type: %d\n", current->word, current->type);
			current = current->next;
		}
		free ((void *)line);
	}
	return (0);
}
