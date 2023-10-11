/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serch_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:51:38 by smizuoch          #+#    #+#             */
/*   Updated: 2023/10/10 15:28:55 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expansion.h"

char	*search_env(char *name, t_env *env)
{
	int			i;
	t_envnode	*tmp;

	if (!env | !env->head | !name)
		return (NULL);
	i = 0;
	tmp = env->head;
	while (name[i] && name[i] != '=')
		i++;
	while (tmp)
	{
		if (tmp->key == NULL)
			return (NULL);
		if (ft_strncmp(tmp->key, name, i) == 0)
		{
			if (tmp->key[i] != '=')
				return (NULL);
			return (tmp->key + i + 1);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

// int main(int argc, char **argv, char **envp)
// {
// 	t_env	env;
// 	char	*str;

// 	env_init(&env, envp);
// 	str = serch_env("PWD", &env);
// 	printf("%s\n", str);
// 	env_clear(&env);
// 	return (0);
// }
