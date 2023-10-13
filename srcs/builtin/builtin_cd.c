/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smizuoch <smizuoch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:40:39 by smizuoch          #+#    #+#             */
/*   Updated: 2023/10/13 15:27:22 by smizuoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"

static void	setoldpwd(t_env *env, char *oldpwd)
{
	t_envnode	*tmp;

	if (!oldpwd || !env || !env->head)
		return ;
	tmp = env->head;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "OLDPWD") == 0
			|| ft_strncmp(tmp->key, "OLDPWD=", 7) == 0)
		{
			free(tmp->key);
			tmp->key = ft_strjoin("OLDPWD=", oldpwd);
			break ;
		}
		tmp = tmp->next;
	}
}

static void	setpwd(t_env *env, char *pwd)
{
	t_envnode	*tmp;

	if (!pwd || !env || !env->head)
		return ;
	tmp = env->head;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PWD") == 0
			|| ft_strncmp(tmp->key, "PWD=", 4) == 0)
		{
			free(tmp->key);
			tmp->key = ft_strjoin("PWD=", pwd);
			break ;
		}
		tmp = tmp->next;
	}
	free (pwd);
}

static int	free_and_return(char *str, int ret)
{
	perror ("chdir");
	if (str)
		free(str);
	return (ret);
}

int	builtin_cd(char **argv, t_env *env)
{
	char		*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		perror ("getcwd");
		return (FAILURE);
	}
	else if (chdir(argv[1]) != 0)
		return (free_and_return(oldpwd, FAILURE));
	setoldpwd(env, oldpwd);
	setpwd(env, getcwd(NULL, 0));
	free(oldpwd);
	return (SUCCESS);
}

// int	env_init(t_env *env, char **envp);

// int	main(int ac, char **av, char **envp)
// {
// 	t_env	env;
// 	t_envnode	*tmp;

// 	(void)ac;
// 	(void)av;
// 	env.head = NULL;
// 	if (env_init(&env, envp) != 0)
// 		return (1);
// 	tmp = env.head;
// 	while (tmp)
// 	{
// 		printf("%s\n", tmp->key);
// 		tmp = tmp->next;
// 	}
// 	printf("----\n");
// 	builtin_cd(av, &env);
// 	tmp = env.head;
// 	while (tmp)
// 	{
// 		printf("%s\n", tmp->key);
// 		tmp = tmp->next;
// 	}
// 	char *str = getcwd(NULL, 0);
// 	printf("%s\n", str);
// 	free(str);
// 	env_clear(&env);
// 	return (0);
// }

// __attribute__((destructor))
// static void destructor(void){
//     system("leaks -q a.out");
// }
