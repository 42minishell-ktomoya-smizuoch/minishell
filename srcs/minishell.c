/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smizuoch <smizuoch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:50:09 by ktomoya           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/09/02 11:29:01 by smizuoch         ###   ########.fr       */
=======
/*   Updated: 2023/08/31 18:23:50 by ktomoya          ###   ########.fr       */
>>>>>>> e4e611e32ecaf2bdc70919108268fffcbaa3a95a
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

int	main()
{
<<<<<<< HEAD
	t_token		*tokens;
	t_token		*current;
	const char	*command;

	while (1)
	{
		command = readline("minishell$ ");
		tokens = tokenize(command);
		current = tokens;
		while (current != NULL)
		{
			printf("Token: %s, Type: %d\n", current->word, current->type);
			current = current->next;
		}
		free ((void *)command);
	}
	return (0);
}
=======
    const char *command = "echo \"Hello,\"\' world!\'";
    t_token     *tokens = tokenize(command);
    t_token      *current = tokens;

    while (current != NULL)
    {
        printf("Token: %s, Type: %d, State: %d\n", current->word, current->type, current->state);
        current = current->next;
    }

    return 0;
}
>>>>>>> e4e611e32ecaf2bdc70919108268fffcbaa3a95a
