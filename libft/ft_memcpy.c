/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmateja <tmateja@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:27:58 by tmateja           #+#    #+#             */
/*   Updated: 2024/09/23 14:16:58 by tmateja          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t len)
{
	unsigned char	*a;
	unsigned char	*b;

	if (!dest && !src)
		return (NULL);
	a = (unsigned char *)dest;
	b = (unsigned char *)src;
	while (len)
	{
		*a++ = *b++;
		--len;
	}
	return (dest);
}
