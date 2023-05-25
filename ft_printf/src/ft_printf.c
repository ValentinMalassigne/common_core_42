/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:06:26 by vmalassi          #+#    #+#             */
/*   Updated: 2023/05/10 16:13:19 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "../includes/ft_printf.h"
#include "../includes/libft.h"

static int	select_convertions(const char *format, va_list args)
{
	if (*format == 'c')
		return (print_char(va_arg(args, int)));
	else if (*format == 's')
		return (print_str(va_arg(args, char *)));
	else if (*format == 'p')
		return (print_ptr(va_arg(args, void *)));
	else if (*format == 'd')
		return (print_deci(va_arg(args, int)));
	else if (*format == 'i')
		return (print_deci(va_arg(args, int)));
	else if (*format == 'u')
		return (print_unsigned(va_arg(args, unsigned int)));
	else if (*format == 'x')
		return (print_hex(va_arg(args, unsigned int), 0));
	else if (*format == 'X')
		return (print_hex(va_arg(args, unsigned int), 1));
	else if (*format == '%')
		return (print_char('%'));
	else
		return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		printed_length;

	printed_length = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
			printed_length += select_convertions(++format, args);
		else
		{
			ft_putchar_fd(*format, 1);
			printed_length++;
		}
		format++;
	}
	va_end(args);
	return (printed_length);
}
