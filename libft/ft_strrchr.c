/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmateja <tmateja@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:47:40 by tmateja           #+#    #+#             */
/*   Updated: 2024/09/20 15:58:13 by tmateja          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned int	i;
	char			*result;
	char			cc;

	cc = (char) c;
	result = NULL;
	i = 0;
	while (s[i])
	{
		if (s[i] == cc)
			result = (char *) &s[i];
		i++;
	}
	if (s[i] == cc)
		result = (char *) &s[i];
	return (result);
}
