/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kudoutomoya <kudoutomoya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:50:09 by ktomoya           #+#    #+#             */
/*   Updated: 2023/08/30 22:47:38 by kudoutomoya      ###   ########.fr       */
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

int main()
{
    const char *command = "echo \"Hello, world!\"";
    t_token_list *tokens = tokenize(command);
    t_token_list *current = tokens;

    while (current != NULL)
    {
        printf("Token: %s, Type: %d\n", current->token.word, current->token.type);
        current = current->next;
    }

    return 0;
}