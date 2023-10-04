/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smizuoch <smizuoch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:33:05 by smizuoch          #+#    #+#             */
/*   Updated: 2023/10/04 15:06:20 by smizuoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"

static bool	check_env(char *env)
{
	int	i;

	i = 0;
	if (!ft_strncmp(env, "_=", 2))
		return (false);
	while (env[i])
	{
		if (env[i] == '=')
			return (true);
		i++;
	}
	return (false);
}

int	builtin_env(char **argv, t_env *env)
{
	int			i;
	char		*underbar;
	t_envnode	*tmp;

	(void)argv;
	if (env == NULL || env->head == NULL)
		return (SUCCESS);
	i = 0;
	tmp = env->head;
	underbar = getenv("_");
	if (!underbar)
		return (FAILURE);
	while (tmp)
	{
		if (check_env(tmp->key))
			ft_putendl_fd(tmp->key, STDOUT_FILENO);
		tmp = tmp->next;
	}
	ft_putstr_fd("_=", STDOUT_FILENO);
	ft_putendl_fd(underbar, STDOUT_FILENO);
	return (SUCCESS);
}

// int	main (int argc, char **argv, char **envp)
// {
// 	(void)argc;
// 	(void)argv;
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
// 	builtin_env(argv, &env);
// 	return (0);
// }
