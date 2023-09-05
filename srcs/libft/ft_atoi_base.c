/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smizuoch <smizuoch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:31:33 by smizuoch          #+#    #+#             */
/*   Updated: 2023/09/05 10:55:10 by smizuoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int	getdigit(char c, int digit)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (c >= 'A' && c <= 'Z' && digit >= 10)
		return (c - 'A' + 10);
	else if (c >= 'a' && c <= 'z' && digit >= 10)
		return (c - 'a' + 10);
	else
		return (-1);
}

int	ft_atoi_base(const char *str, int str_base)
{
	int		result;
	int		sign;
	int		digit;

	result = 0;
	sign = 1;
	digit = 0;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r')
		|| (*str == '-' || *str == '+'))
		str++;
	digit = getdigit(ft_tolower(*str), str_base);
	while (digit >= 0)
	{
		result = result * str_base + digit;
		str++;
		digit = getdigit(ft_tolower(*str), str_base);
	}
	return (result * sign);
}

// int	main(void)
// {
// 	char	*str = "ff";
// 	int		str_base = 16;

// 	printf("%d\n", ft_atoi_base(str, str_base));
// 	return (0);
// }
