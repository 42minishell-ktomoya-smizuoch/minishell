/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smizuoch <smizuoch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 18:25:53 by smizuoch          #+#    #+#             */
/*   Updated: 2023/09/19 18:28:15 by smizuoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "libft.h"
# include <stdio.h>

typedef struct s_env
{
	char			*key;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

#endif