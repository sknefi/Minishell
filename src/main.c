/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmateja <tmateja@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:13:05 by tmateja           #+#    #+#             */
/*   Updated: 2025/05/22 20:54:59 by tmateja          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	shell_loop(t_app *app, int helper);

int	main(int argc, char **argv, char **env)
{
	t_app		*app;
	int			helper;

	(void)argc;
	(void)argv;
	app = init_app(env);
	if (!app)
		return (clean_app(app), EXIT_FAILURE);
	helper = 0;
	sig_handler();
	if (shell_loop(app, helper))
		return (1);
	clean_app(app);
	return (0);
}

static int	shell_loop(t_app *app, int helper)
{
	while (1)
	{
		helper = prompt(app, app->input);
		if (helper == 1)
		{
			free_tokens(app->token);
			continue ;
		}
		else if (helper == -1)
			return (1);
		app->exit_status = helper;
		app->root = parse(app->token, app);
		if (!app->root)
		{
			free(app->input->line);
			free_ast(app->root);
			free_tokens(app->token);
			continue ;
		}
		sh_exec(app);
		free_ast(app->root);
		free_tokens(app->token);
		free(app->input->line);
		app->root = NULL;
	}
}
