/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkarika <fkarika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:13:05 by tmateja           #+#    #+#             */
/*   Updated: 2025/05/16 19:37:34 by fkarika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_app		*app;

	(void)argc;
	(void)argv;
	app = init_app(env);
	if (!app)
		return (clean_app(app), EXIT_FAILURE);
	sig_handler();
	while (1)
	{
		int prompt_res = prompt(app, app->input);
		if (prompt_res == 1)
		{
			free_tokens(app->token);
			continue ;
		}
		else if (prompt_res == -1)
			return (clean_app(app), EXIT_SUCCESS);
		app->exit_status = prompt_res;
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
	clean_app(app);
	return (EXIT_SUCCESS);
}
