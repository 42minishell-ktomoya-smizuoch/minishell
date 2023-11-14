/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 18:25:53 by smizuoch          #+#    #+#             */
/*   Updated: 2023/11/15 08:20:20 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "libft.h"
# include "lexer.h"
# include "parser.h"
# include <stdio.h>

typedef struct s_envnode
{
	char				*key;
	struct s_envnode	*next;
	struct s_envnode	*prev;
}	t_envnode;

//typedef struct s_env
//{
//	struct s_envnode	*head;
//}	t_env;

typedef struct s_env
{
	struct s_envnode	*head;
	char				**envp;
	int					exit_status;
	int					pipe_fd;
}	t_env;

int		env_init(t_env *env, char **envp);
void	env_clear(t_env *env);
char	*search_env(char *name, t_env *env);
char	*search_nenv(const char *name, t_env *env, size_t n);

char	**env_to_envp(t_env *env);
void	*free_env_to_envp(char **envp);

t_node	*expand(t_node *ast, t_env *env);

#endif