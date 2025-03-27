#include "../include/minishell.h"

int		main(int argc, char **argv, char **env)
{
	t_app		*app;
	t_token		*token;
	
	(void)argc;
	(void)argv;
	app = init_app(env);
	if (!app)
		return (EXIT_FAILURE);

	// Test export with various cases
	token = mocked_token_unset();
	token_print(token);

	app->exit_status = sh_exec(app, token);

	p("exit status: %d\n", app->exit_status);
	token_clean(token);
	clean_app(app);
	return (EXIT_SUCCESS);
}
