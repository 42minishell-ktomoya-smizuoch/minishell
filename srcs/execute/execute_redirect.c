/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 10:32:45 by ktomoya           #+#    #+#             */
/*   Updated: 2023/11/25 10:50:53 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"
#include "../../includes/minishell.h"

int	free_retint(void *content, int retnum)
{
	if (content)
		free(content);
	return (retnum);
}

int	parse_file(t_node *node, char **file_here)
{
	if (node->kind == NODE_DLESS
		&& !(node->str[0] == '\"' && node->str[2] == '\0'))
		*file_here = ft_substr(node->str, 0, node->len);
	else if (node->expand_flag == FAILURE)
	{
		puterr_len(node->str, node->len, "ambiguous redirect");
		return (ERROR);
	}
	else if (node->expand)
		*file_here = ft_substr(node->expand, 0, ft_strlen(node->expand));
	else
		*file_here = ft_substr(node->str, 0, node->len);
	if (!*file_here)
		return (putsyserr_retint("malloc", ERROR));
	return (SUCCESS);
}

int	execute_heredocument(char *eof, int fd[4], char **tmp_file)
{
	ft_unlink(*tmp_file);
	if (fd[0] != fd[1])
		restore_fd(fd[0], fd[1]);
	*tmp_file = here_document(eof);
	if (g_signal == 2)
	{
		write (1, "\n", 1);
		free (eof);
		return (ERROR);
	}
	redirect_input(*tmp_file, fd);
	return (SUCCESS);
}

int	execute_redirect(t_node *nd, int fd[4], char **tmp_file)
{
	char	*file;

	while (expect_command(nd))
	{
		if (consume_right(&nd, NODE_ARGUMENT))
			continue ;
		if (parse_file(nd, &file) == ERROR)
			return (ERROR);
		if (nd->kind == NODE_LESS && redirect_input(file, fd) == ERROR)
			return (free_retint(file, ERROR));
		else if (nd->kind == NODE_GREAT && redirect_output(file, fd) == ERROR)
			return (free_retint(file, ERROR));
		else if (nd->kind == NODE_DGREAT && redirect_append(file, fd) == ERROR)
			return (free_retint(file, ERROR));
		else if (nd->kind == NODE_DLESS)
		{
			if (execute_heredocument(file, fd, tmp_file) == ERROR)
				return (ERROR);
		}
		free(file);
		nd = nd->right;
	}
	return (SUCCESS);
}
