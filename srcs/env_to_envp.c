/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smizuoch <smizuoch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:36:15 by smizuoch          #+#    #+#             */
/*   Updated: 2023/10/13 14:08:29 by smizuoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expansion.h"

/*Do not shift the pointer because 
	free_env_to_envp() will not free it correctly.*/
void	*free_env_to_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
	return (NULL);
}

static int	all_len(t_envnode *tmp)
{
	int	len;

	len = 0;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

char	**env_to_envp(t_env *env)
{
	int			i;
	char		**envp;
	t_envnode	*tmp;

	i = 0;
	tmp = env->head;
	envp = (char **)malloc(sizeof(char *) * (all_len(tmp) + 1));
	if (!envp)
		return (NULL);
	tmp = env->head;
	while (tmp)
	{
		envp[i] = ft_strdup(tmp->key);
		if (!envp[i])
			return ((void *)free_env_to_envp(envp));
		tmp = tmp->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_env	env;
// 	char	**envp2;
// 	int		i;

// 	(void)argc;
// 	(void)argv;
// 	i = 0;
// 	env.head = NULL;
// 	env_init(&env, envp);
// 	envp2 = env_to_envp(&env);
// 	while (envp2[i])
// 	{
// 		printf("%s\n", envp2[i]);
// 		i++;
// 	}
// 	free_env_to_envp(envp2);
// 	env_clear(&env);
// 	return (0);
// }
// #include <stdlib.h>
// __attribute__((destructor))
// void	destructor(void)
// {
// 	system("leaks -q a.out");
// }
