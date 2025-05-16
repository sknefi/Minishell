/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmateja <tmateja@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:09:17 by tmateja           #+#    #+#             */
/*   Updated: 2025/05/16 13:04:27 by tmateja          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	handle_char(t_input *input, char **token, \
		size_t *size, t_app *app);
static int	handle_single_quotes(t_input *input, char **token, \
	size_t *size, t_app *app);
static int	handle_double_quotes(t_input *input, char **token, \
	size_t *size, t_app *app);
static int	expand_dollar(t_input *input, char **token, \
		size_t *size, t_app *app);

/*
 * Main function to handle words.
 * Malloc 1 byte for token and assigns null-terminator.
 * If the current char (input->line[input->i]) is not an operator
 * grow token.
 * Returns NULL on error and and token on success.
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
		if (handle_char(input, &token, &size, app))
			return (NULL);
	return (token);
}

/*
 * Function because of norminette.
 * Handles every possible case.
 * Returns 1 on error, 0 on success.
 */

static int	handle_char(t_input *input, char **token, \
		size_t *size, t_app *app)
{
	if (input->line[input->i] == '\'')
	{
		if (handle_single_quotes(input, token, size, app))
			return (1);
	}
	else if (input->line[input->i] == '\"')
	{
		if (handle_double_quotes(input, token, size, app))
			return (1);
	}
	else if (input->line[input->i] == '$')
	{
		if (expand_dollar(input, token, size, app))
			return (1);
	}
	else
	{
		if (grow_token(app, token, size, input->line[input->i++]))
			return (1);
	}
	return (0);
}

/*
 * Expanding single quotes.
 * It is not expanding env variables.
 * If quotes not closed, prinitng error message
 * and changing exit_status and token_error to 1.
 * Returns 1 on error, 0 on success.
 */

static int	handle_single_quotes(t_input *input, char **token, \
	size_t *size, t_app *app)
{
	input->i++;
	while (input->line[input->i] && input->line[input->i] != '\'')
	{
		if (grow_token(app, token, size, input->line[input->i++]))
			return (1);
	}
	if (input->line[input->i] != '\'')
	{
		ft_printf("Syntax error: quotes not closed honey\n");
		input->token_error = 1;
		app->exit_status = ES_ERROR;
	}
	else
		input->i++;
	return (0);
}

/*
 * Handles double quotes.
 * Grow token every char.
 * If current char is dollar sign '$', it expands it.
 * If quotes are not closed, prinitng error message 
 * and changing exit_status and token_error to 1.
 * Returns 1 on error, 0 on success
 */

static int	handle_double_quotes(t_input *input, char **token, \
	size_t *size, t_app *app)
{
	input->i++;
	while (input->line[input->i] && input->line[input->i] != '\"')
	{
		if (input->line[input->i] == '$')
		{
			if (expand_env(input, token, size, app))
				return (1);
		}
		else
		{
			if (grow_token(app, token, size, input->line[input->i++]))
				return (1);
		}
	}
	if (input->line[input->i] != '\"')
	{
		ft_printf("Syntax error: quotes not closed honey\n");
		input->token_error = 1;
		app->exit_status = ES_ERROR;
	}
	else
		input->i++;
	return (0);
}

/*
 * Function decides whether it is $? (to expand exit_status)
 * or env variable.
 * Returns 1 on error, o on success.
 */
static int	expand_dollar(t_input *input, char **token, \
		size_t *size, t_app *app)
{
	if (input->line[input->i + 1] && input->line[input->i + 1] == '?')
	{
		if (expand_exit_status(input, token, size, app))
			return (1);
	}
	else
	{
		if (expand_env(input, token, size, app))
			return (1);
	}
	return (0);
}
