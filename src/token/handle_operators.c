/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmateja <tmateja@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 15:01:11 by tmateja           #+#    #+#             */
/*   Updated: 2025/05/04 19:13:32 by tmateja          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Taking line and index that is iterating in whole line.
 * It creates allocated token with substr.
 * When error, returns NULL.
 * Returns token.
 */

char	*handle_operators(char *line, int *i)
{
	int		start;
	char	*token;

	start = *i;
	if (line[*i + 1])
	{
		if (((line[*i] == '>' && line[*i + 1] == '>') || \
				(line[*i] == '<' && line[*i + 1] == '<')))
		{
			if (line[*i + 2] && (line[*i + 2] != '>' || line[*i + 2] != '>'))
				(*i) += 2;
			else
				return (ft_printf("Syntax error near unexpected token\n"), \
					NULL);
		}
		else
			(*i)++;
	}
	else
		return (ft_printf("Syntax error near unexpected token\n"), NULL);
	token = ft_substr(line, start, *i - start);
	return (token);
}
