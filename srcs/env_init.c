/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smizuoch <smizuoch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:38:20 by smizuoch          #+#    #+#             */
/*   Updated: 2023/09/19 16:43:37 by smizuoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	env_add_back(t_env **env, char *envp)
{
	t_env	*new;
	t_env	*tmp;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (1);
	new->key = ft_strdup(envp);
	if (!new->key)
		return (1);
	new->next = NULL;
	new->prev = NULL;
	if (!(*env))
		*env = new;
	else
	{
		tmp = *env;
		while (tmp->next)
			tmp = tmp->next;
		new->prev = tmp;
		tmp->next = new;
	}
	return (0);
}	

static void	env_clear(t_env **env)
{
	t_env	*tmp;

	while ((*env)->prev)
		*env = (*env)->prev;
	while (*env)
	{
		tmp = *env;
		*env = (*env)->next;
		free(tmp->key);
		free(tmp);
	}
}

static int	add_oldpwd(t_env **env)
{
	int		i;
	char	*oldpwd;
	char	*tmp;

	i = 0;
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
	{
		env_clear(env);
		return (1);
	}
	return (0);
}

int	env_init(t_env **env, char **envp)
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
			ft_putendl_fd("minishell: env: `=': not a valid identifier", 2);
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

// int	main(int argc, char **argv, char **envp)
// {
// 	t_env	*env;

// 	(void)argc;
// 	(void)argv;
// 	env = NULL;
// 	if (env_init(&env, envp) != 0)
// 		return (1);
// 	while (env->next)
// 	{
// 		ft_putendl_fd(env->key, 1);
// 		env = env->next;
// 	}
// 	ft_putendl_fd(env->key, 1);
// 	env_clear(&env);
// 	return (0);
// }

// __attribute__((destructor))
// static void destructor(void){
//     system("leaks -q a.out");
// }
