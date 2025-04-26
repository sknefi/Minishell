/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_low_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmateja <tmateja@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:27:45 by tmateja           #+#    #+#             */
/*   Updated: 2024/10/10 14:37:51 by tmateja          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	ft_num_len(unsigned long long num);

int	ft_low_hex(unsigned long long num)
{
	char	*base;

	base = "0123456789abcdef";
	if (0 == num)
		return (ft_putchar('0'));
	if (16 <= num)
	{
		ft_low_hex(num / 16);
		ft_low_hex(num % 16);
	}
	else
		ft_putchar(base[num % 16]);
	return (ft_num_len(num));
}

static size_t	ft_num_len(unsigned long long num)
{
	int	len;

	len = 0;
	while (0 != num)
	{
		len++;
		num /= 16;
	}
	return (len);
}
