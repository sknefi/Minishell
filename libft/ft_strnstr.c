/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmateja <tmateja@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:52:48 by tmateja           #+#    #+#             */
/*   Updated: 2024/09/23 12:52:49 by tmateja          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	if (little[0] == 0)
		return ((char *)big);
	while (big[x] && x < len)
	{
		while (big[x + y] == little[y] && big[x + y] && x + y < len)
		{
			y++;
			if (little[y] == 0)
				return ((char *) big + x);
		}
		x++;
		y = 0;
	}
	return (0);
}
