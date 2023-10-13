/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smizuoch <smizuoch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:16:40 by smizuoch          #+#    #+#             */
/*   Updated: 2023/10/13 16:46:35 by smizuoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

long long	check_errornoa(long long result, int base, char n, int sign)
{
	long long	over_div;
	long long	over_mod;

	over_div = LONG_MAX / base;
	over_mod = LONG_MAX % base;
	if (errno == ERANGE)
		return (result);
	if (result > over_div || (over_div == result
			&& over_mod < (ft_tolower(n) - 'a' + 10)))
	{
		errno = ERANGE;
		if (sign == 1)
			return (LONG_MAX);
		else
			return (LONG_MIN);
	}
	return (result * base + (ft_tolower(n) - 'a' + 10));
}

long long	check_errornod(long long result, int base, char n, int sign)
{
	long long	over_div;
	long long	over_mod;

	over_div = LONG_MAX / base;
	over_mod = LONG_MAX % base;
	if (errno == ERANGE)
		return (result);
	if (result > over_div || (over_div == result
			&& over_mod < (n - '0')))
	{
		errno = ERANGE;
		if (sign == 1)
			return (LONG_MAX);
		else
			return (LONG_MIN);
	}
	return (result * base + (n - '0'));
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

bool	check_e(char **endptr, const char *nptr, long long *result, int sign)
{
	if (errno == ERANGE)
		return (FAILURE);
	if (endptr)
		*endptr = (char *)nptr;
	*result = *result * sign;
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
		if (ft_isalpha(*nptr) && base > 10)
			result = check_errornoa(result, base, *nptr, sign);
		else if (ft_isdigit(*nptr))
			result = check_errornod(result, base, *nptr, sign);
		else
			errno = EINVAL;
		nptr++;
	}
	check_e(endptr, nptr, &result, sign);
	return (result);
}

// int	main(void)
// {
// 	char	*str = "-3456700000000000000008926";
// 	int		str_base = 10;

// 	errno = 0;
// 	printf("%ld\n", ft_strtol(str, NULL, str_base));
// 	printf("%d\n", errno);
// 	errno = 0;
// 	printf("%ld\n", strtol(str, NULL, str_base));
// 	printf("%d\n", errno);
// 	return (0);
// }
