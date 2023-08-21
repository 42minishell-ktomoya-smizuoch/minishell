/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 14:06:08 by ktomoya           #+#    #+#             */
/*   Updated: 2023/08/16 17:53:25 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static size_t	put_ptr_fd(uintptr_t hexnbr, char *base, int fd)
{
	uintptr_t	base_len;
	size_t		chars;

	chars = 0;
	base_len = ft_strlen(base);
	if (hexnbr >= base_len)
		chars = put_ptr_fd(hexnbr / base_len, base, fd);
	chars += write(fd, &base[hexnbr % base_len], 1);
	return (chars);
}

static size_t	put_uint_fd(unsigned int nbr, char *base, int fd)
{
	uintptr_t	base_len;
	size_t		chars;

	chars = 0;
	base_len = ft_strlen(base);
	if (nbr >= base_len)
		chars = put_uint_fd(nbr / base_len, base, fd);
	chars += write(fd, &base[nbr % base_len], 1);
	return (chars);
}

static size_t	put_int_fd(int nbr, char *base, int fd)
{
	int		base_len;
	size_t	chars;

	chars = 0;
	base_len = ft_strlen(base);
	if (nbr == -2147483648)
	{
		chars = write(fd, "-2147483648", 11);
		return (chars);
	}
	if (nbr < 0)
	{
		chars = write(fd, "-", 1);
		nbr *= -1;
	}
	if (nbr >= base_len)
		chars += put_int_fd(nbr / base_len, base, fd);
	chars += write(fd, &base[nbr % base_len], 1);
	return (chars);
}

static ssize_t	checkflag(const char *flag, va_list args, ssize_t chars, int fd)
{
	if (*flag == 'c')
		chars = ft_putchar_fd(va_arg(args, int), fd);
	else if (*flag == 's')
		chars = ft_putstr_fd(va_arg(args, char *), fd);
	else if (*flag == 'p')
	{
		chars = ft_putstr_fd("0x", fd);
		chars += put_ptr_fd(va_arg(args, uintptr_t), "0123456789abcdef", fd);
	}
	else if (*flag == 'd' || *flag == 'i')
		chars = put_int_fd(va_arg(args, int), "0123456789", fd);
	else if (*flag == 'u')
		chars = put_uint_fd(va_arg(args, unsigned int), "0123456789", fd);
	else if (*flag == 'x')
		chars = put_uint_fd(va_arg(args, unsigned int), "0123456789abcdef", fd);
	else if (*flag == 'X')
		chars = put_uint_fd(va_arg(args, unsigned int), "0123456789ABCDEF", fd);
	else if (*flag == '%')
		chars = ft_putchar_fd('%', fd);
	else
		chars = ft_putchar_fd(*flag, fd);
	return (chars);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	ssize_t	chars;

	va_start(args, format);
	chars = 0;
	while (*format != '\0')
	{
		if (*format == '%')
		{
			format++;
			if (*format != '\0' && ft_strchr("cspdiuxX%%", *format) != NULL)
				chars += checkflag(format, args, chars, STDOUT_FILENO);
			else
				return (chars);
		}
		else
			chars += ft_putchar_fd(*format, STDOUT_FILENO);
		format++;
	}
	va_end(args);
	return ((int)chars);
}
