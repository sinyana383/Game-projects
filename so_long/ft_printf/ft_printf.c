/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 15:49:40 by ddurrand          #+#    #+#             */
/*   Updated: 2022/03/02 15:16:25 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "../so_long.h"

int	print_char(char c)
{
	int	len;

	len = write(1, &c, 1);
	return (len);
}

int	print_string(char *s)
{
	int	len;

	len = 0;
	if ((sizeof(char *) != sizeof(s)))
		return (0);
	if (s != 0)
		len = write(1, s, ft_strlen(s));
	else
		len = write(1, "(null)", 6);
	return (len);
}

int	find_and_write(char c, va_list ap)
{
	int	len;

	len = 0;
	if (c == 'c')
		len = print_char(va_arg(ap, int));
	if (c == 's')
		len = print_string(va_arg(ap, char *));
	if (c == 'p')
		len = print_pointer(va_arg(ap, void *));
	if (c == 'd' || c == 'i')
		len = print_decimal(va_arg(ap, int));
	if (c == 'u')
		len = print_unsigned_int(va_arg(ap, int));
	if (c == 'x')
		len = print_hexadecimal(va_arg(ap, int), 'a');
	if (c == 'X')
		len = print_hexadecimal(va_arg(ap, int), 'A');
	if (c == '%')
		len = print_char('%');
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	char	*end;
	char	*start;
	int		len;

	len = 0;
	va_start(ap, format);
	start = (char *)format;
	while (start && *start)
	{
		end = ft_strchr(start, '%');
		if (!end)
			end = ft_strchr(start, '\0');
		len += write(1, start, end - start);
		end += (*end == '%');
		if (*end)
		{
			len += find_and_write(*end, ap);
		}
		start = end + (*end != '\0');
	}
	va_end(ap);
	return (len);
}
