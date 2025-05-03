/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmateja <tmateja@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:59:20 by tmateja           #+#    #+#             */
/*   Updated: 2025/05/03 16:55:42 by tmateja          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    *ft_realloc_token(void *ptr, size_t size)
{
    void    *new_buffer;

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