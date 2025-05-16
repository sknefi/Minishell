/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmateja <tmateja@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 15:01:11 by tmateja           #+#    #+#             */
/*   Updated: 2025/05/16 13:02:04 by tmateja          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Taking line and index that is iterating in whole line.
 * It creates allocated token with substr.
 * When error, returns NULL.
 * Returns NULL on error, token on success.
 */

char	*handle_operators(t_input *input, t_app *app)
{
	int		start;
	char	*token;

	start = input->i;
	if (input->line[input->i + 1])
	{
		if (((input->line[input->i] == '>' && input->line[input->i + 1] \
			== '>') || (input->line[input->i] == '<' && \
				input->line[input->i + 1] == '<')))
		{
			if (input->line[input->i + 2] && (input->line[input->i + 2] \
				!= '>' || input->line[input->i + 2] != '>'))
				input->i += 2;
			else
				return (ft_printf("Syntax error near unexpected token\n"), \
					app->exit_status = ES_ERROR, NULL);
		}
		else
			input->i++;
	}
	else
		return (ft_printf("Syntax error near unexpected token\n"), \
			app->exit_status = ES_ERROR, NULL);
	token = ft_substr(input->line, start, input->i - start);
	return (token);
}
