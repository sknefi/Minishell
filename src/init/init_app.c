/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_app.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmateja <tmateja@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:18:46 by fkarika           #+#    #+#             */
/*   Updated: 2025/05/24 21:02:50 by tmateja          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	clean_app(t_app *app)
{
	if (app)
	{
		free_env(app->env);
		free_builtins(app->builtins);
		free_tokens(app->token);
		free_ast(app->root);
		if (app->input)
			free(app->input);
		if (app->term_stdout > STDERR_FILENO)
			close(app->term_stdout);
		free(app);
	}
}

t_app	*init_app(char **env)
{
	t_app	*app;

	app = (t_app *)malloc(sizeof(t_app));
	if (!app)
		return (NULL);
	app->input = (t_input *)malloc(sizeof(t_input));
	if (!app->input)
		return (NULL);
	app->env = init_env(env);
	if (!app->env)
		return (NULL);
	app->builtins = init_builtins();
	if (!app->builtins)
		return (NULL);
	app->exit_status = 0;
	app->token = NULL;
	app->root = NULL;
	app->term_stdout = dup(STDOUT_FILENO);
	return (app);
}
