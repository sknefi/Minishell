/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_ptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmateja <tmateja@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:34:14 by tmateja           #+#    #+#             */
/*   Updated: 2024/10/10 17:02:03 by tmateja          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_put_ptr(unsigned long long ptr)
{
	size_t	len;

	len = 0;
	if (0 == ptr)
		return (write(1, "(nil)", 5));
	else
	{
		len += write(1, "0x", 2);
		len += ft_low_hex(ptr);
	}
	return (len);
}
