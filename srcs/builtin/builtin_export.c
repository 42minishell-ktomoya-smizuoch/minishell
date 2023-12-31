/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smizuoch <smizuoch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:32:22 by smizuoch          #+#    #+#             */
/*   Updated: 2023/11/29 15:30:28 by smizuoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"

static void	new_envnode(t_env *env, char *name)
{
	t_envnode	*new;
	t_envnode	*tmp;

	new = (t_envnode *)malloc(sizeof(t_envnode));
	if (!new)
		return ;
	new->next = NULL;
	tmp = env->head;
	while (tmp)
	{
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	new->key = ft_strdup(name);
	tmp->next = new;
	new->prev = tmp;
	if (new->key == NULL)
		return ;
}

static void	ft_setenv(char *name, t_env *env)
{
	int			i;
	t_envnode	*tmp;

	i = 0;
	tmp = env->head;
	while (name[i] && name[i] != '=')
		i++;
	while (tmp)
	{
		if (tmp->key == NULL || i == 0)
			return ;
		if (ft_strncmp(tmp->key, name, i) == 0)
		{
			if (tmp->key[i] == '=' || tmp->key[i] == '\0')
			{
				change_key(name, i, tmp);
				return ;
			}
			else if (ft_strcmp(tmp->key, name) == 0)
				return ;
		}
		tmp = tmp->next;
	}
	new_envnode(env, name);
}

static bool	env_check_alpha(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (false);
	while (str[i])
	{
		if (str[i] == '=')
			return (true);
		if (ft_isalnum(str[i]) == false && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

static int	put_env(t_env *env)
{
	int			i;
	t_envnode	*tmp;

	i = 0;
	tmp = env->head;
	if (!env)
		return (FAILURE);
	while (tmp)
	{
		while (tmp->key[i] && tmp->key[i] != '=')
			i ++;
		printf("declare -x %.*s", i, tmp->key);
		if (tmp->key[i] == '=')
		{
			printf("=\"%s\"", &tmp->key[i + 1]);
		}
		printf("\n");
		tmp = tmp->next;
		i = 0;
	}
	return (SUCCESS);
}

int	builtin_export(char **argv, t_env *env)
{
	int	i;
	int	status;

	i = 1;
	status = SUCCESS;
	if (argv == NULL || argv[1] == NULL)
		return (put_env(env));
	while (argv[i])
	{
		if (env_check_alpha(argv[i]) == false)
		{
			ft_putstr_fd("export: `", STDERR_FILENO);
			ft_putstr_fd(argv[i], STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			status = FAILURE;
		}
		else if (ft_strncmp(argv[1], "_=", 2) != 0
			&& ft_strcmp(argv[i], "_") != 0)
			ft_setenv(argv[i], env);
		i++;
	}
	return (status);
}

// int	main(int argc, char **argv)
// {
// 	(void)argc;
// 	t_env	env;
// 	t_envnode	tmp, tmp2;
// 	env.head = &tmp;
// 	tmp.key = malloc(sizeof(char) * 10);
// 	tmp.key = "OLDPWD=aaa";
// 	tmp.next = &tmp2;
// 	tmp2.key = malloc(sizeof(char) * 10);
// 	tmp2.key = "PWD=bbb";
// 	tmp2.next = NULL;
// 	tmp2.prev = &tmp;
// 	tmp.prev = NULL;
// 	builtin_export(argv, &env);
// 	// put_env(&env); 
// 	return (0);
// }
