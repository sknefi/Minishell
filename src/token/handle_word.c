/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmateja <tmateja@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:09:17 by tmateja           #+#    #+#             */
/*   Updated: 2025/05/09 20:30:02 by tmateja          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handle_single_quotes(t_input *input, char **token, \
	size_t *size, t_app *app);
static void	handle_double_quotes(t_input *input, char **token, \
	size_t *size, t_app *app);
static void	expand_dollar(t_input *input, char **token, \
		size_t *size, t_app *app);

/*
 *
 */

char	*handle_word(t_input *input, t_app *app)
{
	char	*token;
	size_t	size;

	token = malloc(1);
	size = 0;
	if (!token)
		return (NULL);
	token[0] = '\0';
	while (input->line[input->i] && !ft_isspace(input->line[input->i]) \
		&& input->line[input->i] != '|' \
		&& input->line[input->i] != '<' && input->line[input->i] != '>' \
		&& token != NULL)
	{
		if (input->line[input->i] == '\'')
			handle_single_quotes(input, &token, &size, app);
		else if (input->line[input->i] == '\"')
			handle_double_quotes(input, &token, &size, app);
		else if (input->line[input->i] == '$')
			expand_dollar(input, &token, &size, app);
		else
			if (grow_token(&token, &size, input->line[input->i++]))
				return (NULL);
	}
	return (token);
}

static void	handle_single_quotes(t_input *input, char **token, \
	size_t *size, t_app *app)
{
	input->i++;
	while (input->line[input->i] && input->line[input->i] != '\'')
		grow_token(token, size, input->line[input->i++]);
	if (input->line[input->i] != '\'')
	{
		ft_printf("Syntax error: quotes not closed honey\n");
		input->token_error = 1;
		app->exit_status = 1;
	}
	else
		input->i++;
}

/*
 *
 */

static void	handle_double_quotes(t_input *input, char **token, \
	size_t *size, t_app *app)
{
	input->i++;
	while (input->line[input->i] && input->line[input->i] != '\"')
	{
		if (input->line[input->i] == '$')
			expand_env(input, token, size, app);
		else
			grow_token(token, size, input->line[input->i++]);
	}
	if (input->line[input->i] != '\"')
	{
		ft_printf("Syntax error: quotes not closed honey\n");
		input->token_error = 1;
		app->exit_status = 1;
	}
	else
		input->i++;
}

static void	expand_dollar(t_input *input, char **token, \
		size_t *size, t_app *app)
{
	if (input->line[input->i + 1] && input->line[input->i + 1] == '?')
		expand_exit_status(input, token, size, app);
	else
		expand_env(input, token, size, app);
}
