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
// 	p("exit status: %d\n", app->exit_status);
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
		if (prompt(&app->token))
		{
			free_tokens(app->token);
			continue ;
		}
		app->root = parse(app->token);
		if (!app->root)
		{
			free_tokens(app->token);
			free_ast(app->root);
			continue ;
		}
		print_ast(app->root, 0, 0);
		tmp = app->token;
    	while (tmp)
    	{
        	printf("Token: %-10s | Typ: %d\n", tmp->data, tmp->type);
        	tmp = tmp->next;
    	}
		//free_ast(root); broken as in ast node's data are pointer to tokens
		free_tokens(app->token);
		printf("qwe\n");
	}
	clean_app(app);
	return (EXIT_SUCCESS);
}