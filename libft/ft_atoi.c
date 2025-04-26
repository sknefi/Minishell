/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmateja <tmateja@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:53:18 by tmateja           #+#    #+#             */
/*   Updated: 2024/09/23 14:41:05 by tmateja          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	sign;
	int	result;
	int	nb_sign;

	result = 0;
	sign = 1;
	nb_sign = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	while (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		nb_sign++;
		str++;
		if (nb_sign > 1)
			return (0);
	}
	while (*str && *str >= 48 && *str <= 57)
	{
		result *= 10;
		result += *str - 48;
		str++;
	}
	return (result * sign);
}
