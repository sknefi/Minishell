/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmateja <tmateja@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:09:17 by tmateja           #+#    #+#             */
/*   Updated: 2025/05/08 17:06:52 by tmateja          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handle_single_quotes(char *line, int *i, char **token, \
	size_t *size, t_app *app);
static void	handle_double_quotes(char *line, int *i, char **token, \
	size_t *size, t_app *app);
static void	expand_env(char *line, int *i, char **token, size_t *size, t_app *app);
static int	grow_token(char **token, size_t *size, char c);

/*
 *
 */

char	*handle_word(char *line, int *i, t_app *app)
{
	char	*token;
	size_t	size;

	token = malloc(1);
	size = 0;
	if (!token)
		return (NULL);
	token[0] = '\0';
	while (line[*i] && !ft_isspace(line[*i]) && line[*i] != '|' \
		&& line[*i] != '<' && line[*i] != '>' && token != NULL)
	{
		if (line[*i] == '\'')
			handle_single_quotes(line, i, &token, &size, app);
		else if (line[*i] == '\"')
			handle_double_quotes(line, i, &token, &size, app);
		else if (line[*i] == '$')
			expand_env(line, i, &token, &size, app);
		else
			if (grow_token(&token, &size, line[(*i)++]))
				return (NULL);
	}
	return (token);
}

static void	handle_single_quotes(char *line, int *i, char **token, size_t *size, t_app *app)
{
	(*i)++;
	while (line[*i] && line[*i] != '\'')
		grow_token(token, size, line[(*i)++]);
	if (line[*i] != '\'')
	{
			ft_printf("Syntax error: quotes not closed honey\n");
			app->token_error = 1;
			app->exit_status = 1;
	}
	else
		(*i)++;
}

/*
 *
 */

static void	handle_double_quotes(char *line, int *i, char **token, size_t *size, t_app *app)
{
	(*i)++;
	while (line[*i] && line[*i] != '\"')
	{
		if (line[*i] == '$')
			expand_env(line, i, token, size, app);
		else
			grow_token(token, size, line[(*i)++]);
	}
	if (line[*i] != '\"')
	{
		ft_printf("Syntax error: quotes not closed honey\n");
		app->token_error = 1;
		app->exit_status = 1;
	}
	else
		(*i)++;
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

static void	expand_env(char *line, int *i, char **token, size_t *size, t_app *app)
{
	char	var_name[256];
	char	*val;
	int		j;

	j = 0;
	(*i)++;
	if (!ft_isalnum(line[*i]) && line[*i] != '_')
	{
		grow_token(token, size, '$');
		return ;
	}
	while (ft_isalnum(line[*i]) || line[*i] == '_')
	{
		if (j < 255)
			var_name[j++] = line[(*i)++];
		else
			(*i)++;
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
