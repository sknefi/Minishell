/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmateja <tmateja@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:28:02 by tmateja           #+#    #+#             */
/*   Updated: 2024/09/23 13:23:16 by tmateja          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	char	*tmp_src;
	char	*tmp_dest;
	size_t	i;

	if (!dest && !src)
		return (NULL);
	tmp_src = (char *)src;
	tmp_dest = (char *)dest;
	i = 0;
	if (tmp_dest > tmp_src)
	{
		while (len-- > 0)
			tmp_dest[len] = tmp_src[len];
	}
	else
	{
		while (i < len)
		{
			tmp_dest[i] = tmp_src[i];
			i++;
		}
	}
	return (dest);
}
