/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmateja <tmateja@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 21:46:31 by tmateja           #+#    #+#             */
/*   Updated: 2025/05/09 21:08:24 by tmateja          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*find_env(t_app *app, const char *name);
static int	env_to_token(t_app *app, char *val, char **token, size_t *size);

int	grow_token(t_app *app, char **token, size_t *size, char c)
{
	char	*buffer;

	buffer = ft_realloc_token(*token, *size + 2);
	if (!buffer)
		return (app->exit_status = 1, 1); //TODO change to ES_ERROR
	*token = buffer;
	(*token)[(*size)++] = c;
	(*token)[(*size)] = '\0';
	return (0);
}

int	expand_exit_status(t_input *input, char **token, \
		size_t *size, t_app *app)
{
	char	*status;
	size_t	len;
	size_t	i;

	input->i += 2;
	status = ft_itoa(app->exit_status);
	len = ft_strlen(status);
	i = 0;
	while (i < len)
	{
		if (grow_token(app, token, size, status[i++]))
			return (1);
	}
	free(status);
	return (0);
}

int	expand_env(t_input *input, char **token, size_t *size, t_app *app)
{
	char	var_name[256];
	char	*val;
	int		j;

	j = 0;
	input->i++;
	if (!ft_isalnum(input->line[input->i]) && input->line[input->i] != '_')
	{
		grow_token(app, token, size, '$');
		return (0);
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
	if (env_to_token(app, val, token, size))
		return (1);
	return (0);
}

static char	*find_env(t_app *app, const char *name)
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

static int	env_to_token(t_app *app, char *val, char **token, size_t *size)
{
	size_t	i;

	i = 0;
	if (val)
	{
		while (val[i])
		{
			if (grow_token(app, token, size, val[i++]))
				return (1);
			}
	}
	return (0);
}
