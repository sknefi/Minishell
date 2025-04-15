/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmateja <tmateja@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 20:04:01 by tmateja           #+#    #+#             */
/*   Updated: 2024/10/02 20:40:01 by tmateja          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **list, t_list *n)
{
	t_list	*last;

	if (!list || !n)
		return ;
	last = ft_lstlast(*list);
	if (!last)
	{
		*list = n;
		return ;
	}
	last->next = n;
}
