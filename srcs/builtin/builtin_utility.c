/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utility.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smizuoch <smizuoch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:32:44 by smizuoch          #+#    #+#             */
/*   Updated: 2023/12/02 09:48:59 by smizuoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"

void	unset_utility(t_envnode *env, t_env *env_list, int mode)
{
	if (mode == 1)
	{
		free(env->key);
		env->key = NULL;
		free(env);
		return ;
	}
	if (mode == 2)
	{
		env->prev->next = NULL;
		free(env->key);
		env->key = NULL;
		free(env);
		return ;
	}
	if (mode == 3)
	{
		env_list->head = env->next;
		env->next->prev = NULL;
		free(env->key);
		env->key = NULL;
		free(env);
		return ;
	}
}

void	change_key(char *name, int i, t_envnode *tmp)
{
	if (name[i] == '\0')
		return ;
	free(tmp->key);
	tmp->key = NULL;
	tmp->key = ft_strdup(name);
}

void	normal_exit(t_env *env)
{
	write(STDERR_FILENO, "exit\n", 5);
	exit(env->exit_status);
}
