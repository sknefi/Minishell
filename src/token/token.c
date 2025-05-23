/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkarika <fkarika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:03:49 by tmateja           #+#    #+#             */
/*   Updated: 2025/05/23 18:08:48 by fkarika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	tokenization(t_app *app, t_input *input);
static char	*extract_token(t_input *input, t_app *app);
static int	assign_type(char *token);
static char	*get_path(void);

/*
 * Basicly main fucntion for this part of program.
 * Getting prompt from get_path().
 * Reading line, if CTRL + D was pressed, it will exit.
 * If something was typed, then passing token and line to tokenization.
 * Return 1 to main, when fails, 0 on success.
 */

int	prompt(t_app *app, t_input *input)
{
	char	*shell_path;

	app->token = NULL;
	input->line = NULL;
	input->i = 0;
	shell_path = get_path();
	input->line = readline(shell_path);
	free(shell_path);
	if (!input->line)
		return (-1);
	if (input->line[input->i] == 0x0)
		return (free(input->line), 1);
	if (input->line)
	{
		add_history(input->line);
		if (tokenization(app, input))
			return (free(input->line), 1);
	}
	free(app->input->line);
	return (0);
}

/*
 * Tokenization function, takes token and line as parameter.
 * Variable i is for iterating throught line. Every other function has i as 
 * pointer, so they are always changing same i.
 * When found character, its extracting token (extract_token()).
 * Then assigning type and at last appending it.
 * Return 1, when fails, 0 on success.
 */

static int	tokenization(t_app *app, t_input *input)
{
	int		type;
	char	*tmp;

	input->i = 0;
	input->token_error = 0;
	while (input->line[input->i])
	{
		while (input->line[input->i] && ft_isspace(input->line[input->i]))
			input->i++;
		if (!input->line)
			return (1);
		tmp = extract_token(input, app);
		if (NULL == tmp || input->token_error == 1)
			return (1);
		if (tmp && tmp[0] != '\0')
		{
			type = assign_type(tmp);
			app->token = token_append(app->token, tmp, type);
		}
		free(tmp);
	}
	return (0);
}

/*
 * Takes input and app struct.
 * Creates token variable (char).
 * If redirection, then token becomes redirection token.
 * Else creates word token.
 * On error free token and returning NULL.
 * Returns token.
 */

static char	*extract_token(t_input *input, t_app *app)
{
	char	*token;

	token = NULL;
	if (input->line[input->i] == '|' || input->line[input->i] == '<' \
			|| input->line[input->i] == '>')
		token = handle_operators(input, app);
	else
		token = handle_word(input, app);
	if (token && input->token_error == 1)
		free(token);
	if (!token)
		return (NULL);
	return (token);
}

/*
 * Takes token.
 * Assigns token type to token.
 * Returns token.
 */

static int	assign_type(char *token)
{
	if (!ft_strcmp(token, "|"))
		return (TOKEN_PIPE);
	else if (!ft_strcmp(token, ">"))
		return (TOKEN_REDIRECTION_OUT);
	else if (!ft_strcmp(token, "<"))
		return (TOKEN_REDIRECTION_IN);
	else if (!ft_strcmp(token, ">>"))
		return (TOKEN_APPEND);
	else if (!ft_strcmp(token, "<<"))
		return (TOKEN_HEREDOC);
	return (TOKEN_WORD);
}

/*
 * Gets current workind directory and adding "$ " to it
 * making it prompt of our programe.
 * Prompt gets updates every directory change.
 * Prompt is malloc'd, so need to free it afterwards.
 * Returns prompt.
 */

static char	*get_path(void)
{
	char	*str;
	char	*tmp;

	tmp = getcwd(NULL, 0);
	if (!tmp)
		exit(EXIT_FAILURE);
	str = ft_strjoin(tmp, "$ ");
	if (!str)
	{
		free(tmp);
		exit(EXIT_FAILURE);
	}
	free(tmp);
	return (str);
}
