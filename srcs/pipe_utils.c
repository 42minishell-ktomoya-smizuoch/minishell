/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smizuoch <smizuoch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:09:28 by smizuoch          #+#    #+#             */
/*   Updated: 2023/11/22 14:19:48 by smizuoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/execute.h"

t_pipenode	*new_pipenode(t_pipe *a_pipe)
{
	t_pipenode	*new;
	t_pipenode	*tmp;

	new = malloc(sizeof(t_pipenode));
	if (new == NULL)
		exit(1);
	if (a_pipe->top == NULL)
	{
		a_pipe->top = new;
		new->prev = NULL;
		new->next = NULL;
	}
	else
	{
		tmp = a_pipe->top;
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		tmp->next = new;
		new->prev = tmp;
		new->next = NULL;
	}
	return (new);
}

void	free_pipenode(t_pipe *a_pipe)
{
	t_pipenode	*tmp;
	t_pipenode	*tmp2;

	tmp = a_pipe->top;
	while (tmp != NULL)
	{
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
}
