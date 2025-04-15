/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmateja <tmateja@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:39:58 by tmateja           #+#    #+#             */
/*   Updated: 2024/10/01 15:57:41 by tmateja          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*trim_str;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1) - 1;
	while (ft_strrchr(set, s1[start]) && start <= end)
		start++;
	if (start > end)
		return (ft_strdup(s1 + end +1));
	while (ft_strrchr(set, s1[end]) && end >= 0)
		end--;
	trim_str = malloc(end - start + 2);
	if (!trim_str)
		return (NULL);
	ft_strlcpy(trim_str, &s1[start], end - start + 2);
	return (trim_str);
}
