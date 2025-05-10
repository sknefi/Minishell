/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmateja <tmateja@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:59:20 by tmateja           #+#    #+#             */
/*   Updated: 2025/05/04 16:23:40 by tmateja          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Realloc for tokens.
 * Because it's used only in handle_word, everytime it has been caled
 * the old size is size - 2.
 * Returns the same as man 3 realloc.
 */

void	*ft_realloc_token(void *ptr, size_t size)
{
	void	*new_buffer;

	if (!ptr)
		return (malloc(size));
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_buffer = malloc(size);
	if (!new_buffer)
		return (NULL);
	ft_memcpy(new_buffer, ptr, size - 2);
	free(ptr);
	return (new_buffer);
}
