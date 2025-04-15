/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_upper_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmateja <tmateja@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:27:41 by tmateja           #+#    #+#             */
/*   Updated: 2024/10/10 14:39:00 by tmateja          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_upper_hex(unsigned long long num)
{
	size_t		len;
	char		*base;

	len = 0;
	base = "0123456789ABCDEF";
	if (16 <= num)
	{
		len += ft_upper_hex(num / 16);
		len += ft_upper_hex(num % 16);
	}
	else
		len += ft_putchar(base[num % 16]);
	return (len);
}
