/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smizuoch <smizuoch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 18:25:53 by smizuoch          #+#    #+#             */
/*   Updated: 2023/10/04 17:13:27 by smizuoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "libft.h"
# include <stdio.h>

typedef struct s_envnode
{
	char				*key;
	struct s_envnode	*next;
	struct s_envnode	*prev;
}	t_envnode;

typedef struct s_env
{
	struct s_envnode	*head;
	char				**envp;
}	t_env;

int		env_init(t_env *env, char **envp);
void	env_clear(t_env *env);

#endif