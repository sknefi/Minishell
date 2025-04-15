/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmateja <tmateja@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:28:06 by tmateja           #+#    #+#             */
/*   Updated: 2024/09/20 15:01:44 by tmateja          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *buffer, int value, size_t len)
{
	unsigned char	*ptr;

	ptr = buffer;
	while (len--)
		*ptr++ = value;
	return (buffer);
}
