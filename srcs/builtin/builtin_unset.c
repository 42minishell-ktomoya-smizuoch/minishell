/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smizuoch <smizuoch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:32:44 by smizuoch          #+#    #+#             */
/*   Updated: 2023/10/03 17:08:43 by smizuoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"

static void	ft_shift_env(t_envnode *env)
{
	t_envnode	*tmp;

	tmp = env;
	if (env->next == NULL && env->prev == NULL)
	{
		free(env->key);
		env->key = NULL;
		free(env);
		return ;
	}
	else if (env->next == NULL && env->prev != NULL)
	{
		env->prev->next = NULL;
		free(env->key);
		env->key = NULL;
		free(env);
		return ;
	}
	else if (env->next != NULL && env->prev == NULL)
	{
		env->next->prev = NULL;
		free(env->key);
		env->key = NULL;
		free(env);
		return ;
	}
	env->prev->next = env->next;
	env->next->prev = env->prev;
	free(env->key);
	env->key = NULL;
	free(env);
	return ;
}

static void	ft_unsetenv(char *name, t_env *env)
{
	char		*newname;
	t_envnode	*tmp;

	tmp = env->head;
	newname = ft_strjoin(name, "=");
	if (!newname)
		return ;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, newname, ft_strlen(newname)) == 0
			|| ft_strcmp(tmp->key, name) == 0)
		{
			free(newname);
			ft_shift_env(tmp);
			return ;
		}
		tmp = tmp->next;
	}
	free(newname);
	return ;
}

static int	ft_getenv(char *name, t_env *env)
{
	char		*newname;
	t_envnode	*tmp;

	tmp = env->head;
	newname = ft_strjoin(name, "=");
	if (!newname)
		return (0);
	while (tmp)
	{
		if (ft_strncmp(tmp->key, newname, ft_strlen(newname)) == 0
			|| ft_strcmp(tmp->key, name) == 0)
		{
			free(newname);
			return (1);
		}
		tmp = tmp->next;
	}
	free(newname);
	return (0);
}

static bool	env_check_alpha(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (false);
	while (str[i])
	{
		if (ft_isalnum(str[i]) == false && str[i] != '_')
			return (false);
		if (str[i] == '=')
			return (false);
		i++;
	}
	return (true);
}

int	builtin_unset(char **argv, t_env *env)
{
	int	i;

	i = 1;
	if (argv == NULL || argv[1] == NULL)
		return (0);
	while (argv[i])
	{
		if (env_check_alpha(argv[i]) == false)
		{
			ft_putstr_fd("unset: `", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			return (1);
		}
		if (ft_getenv(argv[i], env))
			ft_unsetenv(argv[i], env);
		i++;
	}
	return (0);
}

// #include "../../includes/expansion.h"
// int	main(int ac, char **av , char **envp)
// {
// 	(void)ac;
// 	t_env	env;
// 	env_init(&env, envp);
// 	builtin_unset(av, &env);
// 	while (env.head)
// 	{
// 		printf("%s\n", env.head->key);
// 		env.head = env.head->next;
// 	}
// 	return (0);
// }
