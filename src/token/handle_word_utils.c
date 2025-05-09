/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmateja <tmateja@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 21:46:31 by tmateja           #+#    #+#             */
/*   Updated: 2025/05/09 20:47:15 by tmateja          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*find_env(t_app *app, const char *name);
static void	env_to_token(char *val, char **token, size_t *size);

int	grow_token(char **token, size_t *size, char c)
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

void	expand_exit_status(t_input *input, char **token, \
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
		grow_token(token, size, status[i++]);
	free(status);
}

void	expand_env(t_input *input, char **token, size_t *size, t_app *app)
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
	env_to_token(val, token, size);
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

static void	env_to_token(char *val, char **token, size_t *size)
{
	size_t	i;

	i = 0;
	if (val)
	{
		while (val[i])
			grow_token(token, size, val[i++]);
	}
}
