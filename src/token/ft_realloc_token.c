/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkarika <fkarika@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:59:20 by tmateja           #+#    #+#             */
/*   Updated: 2025/05/03 18:44:14 by fkarika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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