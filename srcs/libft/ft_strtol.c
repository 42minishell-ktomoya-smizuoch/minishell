/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smizuoch <smizuoch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:16:40 by smizuoch          #+#    #+#             */
/*   Updated: 2023/09/06 17:07:40 by smizuoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

long int	charck_errornoa(long result, int base, char n, int sign)
{
	long long	i;

	i = 0;
	i = result * base * sign + (ft_tolower(n) - 'a' + 10);
	if (i > LONG_MAX)
	{
		errno = ERANGE;
		return (LONG_MAX);
	}
	else if (i < LONG_MIN)
	{
		errno = ERANGE;
		return (LONG_MIN);
	}
	return (i);
}

long int	chaeck_errornod(long result, int base, char n, int sign)
{
	long long	i;

	i = 0;
	i = result * base * sign + (n - '0');
	if (i > LONG_MAX)
	{
		errno = ERANGE;
		return (LONG_MAX);
	}
	else if (i < LONG_MIN)
	{
		errno = ERANGE;
		return (LONG_MIN);
	}
	return (i);
}

int	chaeck_base(int base)
{
	if (base < 2 || base > 36)
	{
		errno = EINVAL;
		return (FAILURE);
	}
	return (SUCCESS);
}

long int	ft_strtol(const char *nptr, char **endptr, int base)
{
	long long	result;
	int			sign;

	result = 0;
	sign = 1;
	if (chaeck_base(base) == FAILURE)
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
			result = chaeck_errornod(result, base, *nptr, sign);
		else if (ft_isalpha(*nptr) && base > 10)
			result = charck_errornoa(result, base, *nptr, sign);
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
