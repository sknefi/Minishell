/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_unum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmateja <tmateja@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:27:37 by tmateja           #+#    #+#             */
/*   Updated: 2024/10/10 14:40:19 by tmateja          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_put_unum(unsigned int num)
{
	size_t	len;

	len = 0;
	if (9 < num)
	{
		len += ft_put_unum(num / 10);
		len += ft_put_unum(num % 10);
	}
	else
		len += ft_putchar(num + 48);
	return (len);
}
