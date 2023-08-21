/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 18:01:55 by ktomoya           #+#    #+#             */
/*   Updated: 2023/08/03 17:20:50 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static size_t	count_digits(int nb)
{
	size_t	count;

	count = 1;
	while (nb / 10 != 0)
	{
		count++;
		nb /= 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char		*str;
	size_t		digit;
	long int	num;

	num = n;
	digit = count_digits(n);
	if (n < 0)
	{
		num = -num;
		digit++;
	}
	str = (char *)ft_calloc(digit + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	while (digit--)
	{
		str[digit] = num % 10 + '0';
		num /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
