/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:45:00 by ktomoya           #+#    #+#             */
/*   Updated: 2023/08/21 18:59:31 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	display_prompt(void)
{
	char	*input;

	while (1)
	{
		// ユーザーからの入力を取得する
		input = readline("minishell$");
		// readline関数は入力が行われなかった場合はNULLを返すことがある
		if (!input)
			exit(FAILURE);
		printf("%s\n", input);
		// 入力内容を履歴として保存する
		add_history(input);
		// 必要ならば、inputをfreeしてメモリを解放する
		free(input);
	}
	return (SUCCESS);
}
