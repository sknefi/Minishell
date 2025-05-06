#include "../include/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_app		*app;
	t_token		*tmp;

	// TYM was here
	(void)argc;
	(void)argv;
	app = init_app(env);
	if (!app)
		return (EXIT_FAILURE);
	sig_handler();
	while (1)
	{
		int prompt_res = prompt(&app->token, &app->root);
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
		printf(Y "exit status: %d\n" RST, app->exit_status);
		free_ast(app->root);
		free_tokens(app->token);
		app->root = NULL;
	}
	clean_app(app);
	return (EXIT_SUCCESS);
}