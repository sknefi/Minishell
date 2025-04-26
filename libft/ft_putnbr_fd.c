/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmateja <tmateja@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:13:38 by tmateja           #+#    #+#             */
/*   Updated: 2024/09/23 12:50:18 by tmateja          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nbl;
	short	i;
	char	num[10];

	nbl = n;
	i = 0;
	if (n == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	if (nbl < 0)
	{
		nbl *= -1;
		write(fd, "-", 1);
	}
	while (nbl != 0)
	{
		num[i++] = (nbl % 10) + 48;
		nbl /= 10;
	}
	while (i > 0)
		write(fd, &num[--i], 1);
}
