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
	token = mocked_token_export();
	p("\nTesting export command with various cases:\n");
	token_print(token);
	exec_builtin("export", token, app);

	token_clean(token);
	clean_app(app);
	return 0;
}
