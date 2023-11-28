/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smizuoch <smizuoch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:38:20 by smizuoch          #+#    #+#             */
/*   Updated: 2023/11/25 17:23:02 by smizuoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expansion.h"

static int	env_add_back(t_env *env, char *envp)
{
	t_envnode	*new;
	t_envnode	*tmp;

	new = (t_envnode *)malloc(sizeof(t_envnode));
	if (!new)
		return (1);
	new->key = ft_strdup(envp);
	if (!new->key)
		return (1);
	new->next = NULL;
	new->prev = NULL;
	if (!env->head)
		env->head = new;
	else
	{
		tmp = env->head;
		while (tmp->next)
			tmp = tmp->next;
		new->prev = tmp;
		tmp->next = new;
	}
	return (0);
}

void	env_clear(t_env *env)
{
	t_envnode	*tmp;

	while (env->head)
	{
		tmp = env->head;
		env->head = env->head->next;
		if (tmp->key)
			free(tmp->key);
		free(tmp);
	}
}

static int	add_oldpwd(t_env *env)
{
	int			i;
	char		*oldpwd;
	t_envnode	*tmp;

	i = 0;
	tmp = env->head;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "OLDPWD") == 0
			|| ft_strncmp(tmp->key, "OLDPWD=", 7) == 0)
			return (0);
		tmp = tmp->next;
	}
	oldpwd = ft_calloc(7, sizeof(char));
	if (!oldpwd)
	{
		env_clear(env);
		return (1);
	}
	oldpwd = ft_memcpy(oldpwd, "OLDPWD", 6);
	i = env_add_back(env, oldpwd);
	free(oldpwd);
	if (i != 0)
		env_clear(env);
	return (i);
}

int	env_init(t_env *env, char **envp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (envp[i] != NULL)
	{
		if (envp[i][0] == '\0')
			break ;
		if (envp[i][0] == '=')
		{
			ft_putendl_fd("env: `=': not a valid identifier", 2);
			return (1);
		}
		if (envp[i][0] != '\0')
			j = env_add_back(env, envp[i]);
		if (j != 0)
		{
			env_clear(env);
			return (1);
		}
		i++;
	}
	return (add_oldpwd(env));
}

// int	main(int ac, char **av, char **envp)
// {
// 	t_env	env;

// 	(void)ac;
// 	(void)av;
// 	env.head = NULL;
// 	if (env_init(&env, envp) != 0)
// 		return (1);
// 	t_envnode	*tmp;
// 	tmp = env.head;
// 	while (tmp)
// 	{
// 		printf("%s\n", tmp->key);
// 		tmp = tmp->next;
// 	}
// 	env_clear(&env);
// 	return (0);
// }

// __attribute__((destructor))
// static void destructor(void){
//     system("leaks -q a.out");
// }
