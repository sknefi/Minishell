#include "../include/minishell.h"

// t_input	*init_input(void)
// {
// 	t_input	*input;

// 	input = NULL;
// 	input->i = 0;
// 	input->line = NULL;
// 	return(input);
// }

int	main(int argc, char **argv, char **env)
{
	t_app		*app;
	t_input		*input;
	t_token		*tmp;

	// TYM was here
	(void)argc;
	(void)argv;
	app = init_app(env);
	input = malloc(sizeof(t_input));
	if (!input)
		return (free(app), EXIT_FAILURE);
	if (!app)
		return (EXIT_FAILURE);
	sig_handler();
	while (1)
	{
		int prompt_res = prompt(app, input);
		if (prompt_res == 1)
		{
			free_tokens(app->token);
			continue ;
		}
		else if (prompt_res == -1)
			return (clean_app(app), free(input), EXIT_FAILURE);
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
