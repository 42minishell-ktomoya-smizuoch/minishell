/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset_utility.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smizuoch <smizuoch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:32:44 by smizuoch          #+#    #+#             */
/*   Updated: 2023/11/19 16:34:33 by smizuoch         ###   ########.fr       */
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
