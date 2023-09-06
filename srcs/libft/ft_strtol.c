/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smizuoch <smizuoch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:16:40 by smizuoch          #+#    #+#             */
/*   Updated: 2023/09/05 11:24:01 by smizuoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

long int	ft_strtol(const char *nptr, char **endptr, int base)
{
	long long	result;
	int			sign;

	result = 0;
	sign = 1;
	if (base < 2 || base > 36)
		return (0);
	while (*nptr == ' ' || (*nptr >= '\t' && *nptr <= '\r'))
		nptr++;
	if (*nptr == '-')
		sign = -1;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while (ft_isalnum(*nptr))
	{
		if (ft_isdigit(*nptr))
			result = result * base + (*nptr - '0');
		else if (ft_isalpha(*nptr) && base > 10)
			result = result * base + (ft_tolower(*nptr) - 'a' + 10);
		nptr++;
	}
	if (endptr)
		*endptr = (char *)nptr;
	return (result * sign);
}

// int	main(void)
// {
// 	char	*str = "3050abc";
// 	int		str_base = 10;

// 	printf("%ld\n", ft_strtol(str, NULL, str_base));
// 	return (0);
// }
