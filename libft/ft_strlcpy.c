/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmateja <tmateja@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:28:11 by tmateja           #+#    #+#             */
/*   Updated: 2024/09/23 13:32:17 by tmateja          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t len)
{
	size_t	src_len;

	src_len = ft_strlen(src);
	if (src_len + 1 < len)
		ft_memcpy(dest, src, src_len + 1);
	else if (len != 0)
	{
		ft_memcpy(dest, src, len - 1);
		dest[len - 1] = '\0';
	}
	return (src_len);
}
