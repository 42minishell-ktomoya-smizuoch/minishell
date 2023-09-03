/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:17:52 by ktomoya           #+#    #+#             */
/*   Updated: 2023/09/03 16:57:26 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// t_token	*create_token(const char *str, enum e_state prev_state)
// {
// 	t_token	*new;

// 	new = (t_token *)ft_xmalloc(sizeof(t_token));
// 	if (!new)
// 		set_errno_and_exit("malloc error\n", ENOMEM);
// 	new->type = get_token_type(str);
// 	new->len = get_token_len(str, prev_state);
// 	new->word = ft_substr(str, 0, new->len);
// 	new->next = NULL;
// 	return (new);
// }
