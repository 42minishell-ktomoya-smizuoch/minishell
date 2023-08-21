/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:46:27 by ktomoya           #+#    #+#             */
/*   Updated: 2023/08/03 17:20:31 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int	plus_atoi(const char *str, int sign)
{
	size_t		i;
	long int	over_div;
	long int	over_mod;
	long int	num;

	i = 0;
	over_div = LONG_MAX / 10;
	over_mod = LONG_MAX % 10;
	num = 0;
	while ('0' <= str[i] && str[i] <= '9')
	{
		if (num > over_div || (over_div == num && over_mod < str[i] - '0'))
		{
			if (sign == 1)
				return ((int)LONG_MAX);
			else
				return ((int)LONG_MIN);
		}
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return ((int)num);
}

int	ft_atoi(const char *str)
{
	size_t	i;
	int		num;
	int		sign;

	i = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	num = plus_atoi(&str[i], sign);
	return (sign * num);
}
