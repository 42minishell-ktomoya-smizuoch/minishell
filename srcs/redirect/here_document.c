/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smizuoch <smizuoch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:35:49 by smizuoch          #+#    #+#             */
/*   Updated: 2023/11/10 13:52:29 by smizuoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/redirect.h"
#include "../../includes/minishell.h"

int	g_signal;

static int	search_file(char *here_doc)
{
	if (access(here_doc, F_OK) == 0)
		return (1);
	return (-1);
}

char	*here_document(char *limiter)
{
	int			fd;
	int			fd2;
	int			ret;
	const char	*line;
	char		hear_doc[36];

	fd2 = dup(0);
	ret = 34;
	ft_memset(hear_doc, 0, 36);
	ft_memcpy(hear_doc, "/tmp/.here_doc_aaaaaaaaaaaaaaaaaaaa", 35);
	while (search_file(hear_doc) != -1)
	{
		hear_doc[ret]++;
		if (hear_doc[ret] == 'z')
			ret -= 1;
		if (ret == 15)
		{
			ft_putendl_fd("too many here documents", 2);
			return (NULL);
		}
	}
	fd = open(hear_doc, O_RDWR | O_CREAT, 0644);
	if (fd == -1)
	{
		ft_putendl_fd("open error", 2);
		return (NULL);
	}
	while (1)
	{
		set_signal(2);
		line = readline("> ");
		if (g_signal == 1)
		{
			dup2(fd2, 0);
			break ;
		}
		if (!line)
			break ;
		if (ft_strcmp(line, limiter) == 0)
			break ;
		ft_putendl_fd(line, fd);
		free((void *)line);
	}
	free((void *)line);
	ft_putstr_fd("\0", fd);
	close(fd);
	close(fd2);
	return (ft_strdup(hear_doc));
}

// int	main(void)
// {
// 	char *hear_doc;
// 	hear_doc = here_document("limiter");
// 	unlink(hear_doc);
// 	return (0);
// }
