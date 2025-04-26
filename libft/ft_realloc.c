/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmateja <tmateja@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 15:28:19 by tmateja           #+#    #+#             */
/*   Updated: 2024/11/10 18:08:17 by tmateja          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_realloc(volatile char **str, int new_len, int old_len)
{
	char	*new_str;
	int		i;

	new_str = malloc(sizeof(char) * new_len);
	if (!new_str)
	{
		ft_printf("Malloc Failed\n");
		exit(1);
	}
	i = 0;
	while (i < old_len)
	{
		new_str[i] = (*str)[i];
		i++;
	}
	free((void *)*str);
	*str = new_str;
}
