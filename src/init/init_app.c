#include "../../include/minishell.h"

void	clean_app(t_app *app)
{
	if (app)
	{
		if (app->builtins)
			free_builtins(app->builtins);
		free(app);
	}
}

t_app	*init_app(char **env)
{
	t_app	*app;

	app = (t_app *)malloc(sizeof(t_app));
	if (!app)
		return (NULL);
	app->env = env;
	app->builtins = init_builtins();
	if (!app->builtins)
		return (clean_app(app), NULL);
	app->exit_status = 0;
	return (app);
}
