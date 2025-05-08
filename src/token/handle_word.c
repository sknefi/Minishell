/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmateja <tmateja@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:09:17 by tmateja           #+#    #+#             */
/*   Updated: 2025/05/08 19:03:22 by tmateja          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handle_single_quotes(t_input *input, char **token, \
	size_t *size, t_app *app);
static void	handle_double_quotes(t_input *input, char **token, \
	size_t *size, t_app *app);
static void	expand_env(t_input *input, char **token, size_t *size, t_app *app);
static int	grow_token(char **token, size_t *size, char c);

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
			expand_env(input, &token, &size, app);
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
		app->token_error = 1;
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
		app->token_error = 1;
		app->exit_status = 1;
	}
	else
		input->i++;
}

char	*find_env(t_app *app, const char *name)
{
	size_t	len;
	size_t	i;

	if (!app || !app->env || !name)
		return (NULL);
	i = 0;
	len = ft_strlen(name);
	while (app->env[i])
	{
		if (ft_strncmp(app->env[i], name, len) == 0 && app->env[i][len] == '=')
			return (app->env[i] + len + 1);
		i++;
	}
	return (NULL);
}

static void	expand_env(t_input *input, char **token, size_t *size, t_app *app)
{
	char	var_name[256];
	char	*val;
	int		j;

	j = 0;
	input->i++;
	if (!ft_isalnum(input->line[input->i]) && input->line[input->i] != '_')
	{
		grow_token(token, size, '$');
		return ;
	}
	while (ft_isalnum(input->line[input->i]) || input->line[input->i] == '_')
	{
		if (j < 255)
			var_name[j++] = input->line[input->i++];
		else
			input->i++;
	}
	var_name[j] = '\0';
	val = find_env(app, var_name);
	j = 0; //temp
	if (val)
	{
		printf("%s\n", val);
		//env_token();
		while (val[j])
		{
			grow_token(token, size, val[j]);
			j++;
		}
	}
}

/*
 *
 */

static int	grow_token(char **token, size_t *size, char c)
{
	char	*buffer;

	buffer = ft_realloc_token(*token, *size + 2);
	if (!buffer)
		return (1);
	*token = buffer;
	(*token)[(*size)++] = c;
	(*token)[(*size)] = '\0';
	return (0);
}
