/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smizuoch <smizuoch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 18:25:53 by smizuoch          #+#    #+#             */
/*   Updated: 2023/11/29 15:26:00 by smizuoch         ###   ########.fr       */
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

int		expand(t_node *ast, t_env *env);
bool	is_expandable(const char *s, size_t len);
size_t	count_len(const char *line, t_env *env);
size_t	count_digits(int num);
t_state	update_state(const char c, t_state prev);
void	copy_expand(char *dst, const char *src, t_env *env);

#endif