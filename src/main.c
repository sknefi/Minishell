#include "../include/minishell.h"

int		main(int argc, char **argv, char **env)
{
	int	i;
	t_app		*app;
	t_token		*token;
	
	(void)argc;
	(void)argv;
	app = init_app(env);
	if (!app)
		return (EXIT_FAILURE);
	token = mocked_token_cd();
	(void)i;
	token_print(token);
	exec_builtin("cd", token, app);

	token_clean(token);
	clean_app(app);
	return 0;
}
