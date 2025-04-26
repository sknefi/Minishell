/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmateja <tmateja@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:17:16 by tmateja           #+#    #+#             */
/*   Updated: 2024/10/10 16:00:05 by tmateja          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_format(va_list *args, const char format);

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		len;
	int		i;

	len = 0;
	i = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			len += ft_format(&args, str[i + 1]);
			i++;
		}
		else
			len += ft_putchar(str[i]);
		i++;
	}
	va_end(args);
	return (len);
}

static int	ft_format(va_list *args, const char format)
{
	int	len;

	len = 0;
	if (format == 'c')
		len += ft_putchar(va_arg(*args, int));
	else if (format == 's')
		len += ft_put_str(va_arg(*args, char *));
	else if (format == 'p')
		len += ft_put_ptr(va_arg(*args, unsigned long long));
	else if (format == 'd')
		len += ft_put_num(va_arg(*args, int));
	else if (format == 'i')
		len += ft_put_num(va_arg(*args, int));
	else if (format == 'u')
		len += ft_put_unum(va_arg(*args, unsigned int));
	else if (format == 'x')
		len += ft_low_hex(va_arg(*args, unsigned int));
	else if (format == 'X')
		len += ft_upper_hex(va_arg(*args, unsigned int));
	else if (format == '%')
		len += ft_putchar('%');
	return (len);
}
