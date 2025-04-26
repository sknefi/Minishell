/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmateja <tmateja@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:52:57 by tmateja           #+#    #+#             */
/*   Updated: 2024/10/01 15:58:31 by tmateja          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_len(int num);

char	*ft_itoa(int n)
{
	char		*str;
	size_t		len;
	int			sign;

	sign = n < 0;
	len = get_len(n) + sign;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[len] = 0;
	if (sign)
	{
		*str = '-';
		str[--len] = -(n % 10) + '0';
		n = -(n / 10);
	}
	while (len-- - sign)
	{
		str[len] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}

static size_t	get_len(int num)
{
	size_t	len;

	len = !num;
	while (num)
	{
		num /= 10;
		len++;
	}
	return (len);
}
