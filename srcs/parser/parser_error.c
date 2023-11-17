/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 08:26:20 by ktomoya           #+#    #+#             */
/*   Updated: 2023/11/16 08:38:53 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	put_syntax_error(t_token *tok)
{
	ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
	if (tok && tok->type == TYPE_PIPE)
		ft_putstr_fd("|", STDERR_FILENO);
	else if (tok && tok->type == TYPE_GREAT)
		ft_putstr_fd(">", STDERR_FILENO);
	else if (tok && tok->type == TYPE_LESS)
		ft_putstr_fd("<", STDERR_FILENO);
	else if (tok && tok->type == TYPE_DGREAT)
		ft_putstr_fd(">>", STDERR_FILENO);
	else if (tok && tok->type == TYPE_DLESS)
		ft_putstr_fd("<<", STDERR_FILENO);
	else if (tok && tok->type == TYPE_GENERAL)
		write(STDERR_FILENO, tok->str, tok->len);
	else if (tok && tok->type == TYPE_EOF)
		ft_putstr_fd("newline", STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
}

void	*syntax_error_null(t_token *tok)
{
	put_syntax_error(tok);
	return (NULL);
}
