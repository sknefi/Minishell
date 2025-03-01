#include "../include/minishell.h"

int		main(int argc, char **argv, char **env)
{
	char		**av;
	t_app		*app;
	t_token		*token;
	(void)argc;
	(void)argv;

	app = init_app(env);
	if (!app)
		return (EXIT_FAILURE);
	exec_builtin("echo", token, app);
	
	
	// p("builtins[4]->name: %s\n", builtins[4]->name);
	// p("PATH: %s\n", get_env_var("PATH", env));
	clean_app(app);
	return 0;
}
