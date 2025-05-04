/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_num.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmateja <tmateja@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 18:46:51 by tmateja           #+#    #+#             */
/*   Updated: 2024/10/10 14:40:40 by tmateja          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_put_num(int num)
{
	size_t	len;

	len = 0;
	if (num == -2147483648)
		return (write(1, "-2147483648", 11));
	if (0 > num)
	{
		len += write(1, "-", 1);
		num *= -1;
	}
	if (9 < num)
	{
		len += ft_put_num(num / 10);
		len += ft_put_num(num % 10);
	}
	else
		len += ft_putchar(num + 48);
	return (len);
}
