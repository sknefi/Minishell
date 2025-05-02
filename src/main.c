#include "../include/minishell.h"

// int		main(int argc, char **argv, char **env)
// {
// 	t_app		*app;
// 	t_token		*token;
	
// 	(void)argc;
// 	(void)argv;
// 	app = init_app(env);
// 	if (!app)
// 		return (EXIT_FAILURE);

// 	// Test export with various cases
// 	token = mocked_token_unset();
// 	token_print(token);

// 	app->exit_status = sh_exec(app, token);
// 	if (app->exit_status == -1)
// 		return (EXIT_FAILURE);
// 	ft_printf("exit status: %d\n", app->exit_status);
// 	token_clean(token);
// 	clean_app(app);
// 	return (EXIT_SUCCESS);
// }

int	main(int argc, char **argv, char **env)
{
	t_app		*app;
	t_token		*tmp;

	(void)argc;
	(void)argv;
	app = init_app(env);
	if (!app)
		return (EXIT_FAILURE);
	sig_handler();
	while (1)
	{
		int prompt_res = prompt(&app->token, app);
		if (prompt_res == 1)
		{
			free_tokens(app->token);
			continue ;
		}
		else if (prompt_res == -1)
			return (clean_app(app), EXIT_FAILURE);
		app->exit_status = prompt_res;
		app->root = parse(app->token);
		if (!app->root)
		{
			free_tokens(app->token);
			continue ;
		}
		print_ast(app->root, 0, 0);
		tmp = app->token;
    	while (tmp)
    	{
        	printf("Token: %-10s | Typ: %d\n", tmp->data, tmp->type);
        	tmp = tmp->next;
    	}
		sh_exec(app);
		free_ast(app->root);
		free_tokens(app->token);
		app->root = NULL;
	}
	clean_app(app);
	return (EXIT_SUCCESS);
}