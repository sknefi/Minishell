#include "../../include/minishell.h"

void	clean_app(t_app *app)
{
	if (app)
	{
		free_env(app->env);
		free_builtins(app->builtins);
		free_tokens(app->token);
		free_ast(app->root);
		free(app);
	}
}

t_app	*init_app(char **env)
{
	t_app	*app;

	app = (t_app *)malloc(sizeof(t_app));
	if (!app)
		return (NULL);
	app->env = init_env(env);
	if (!app->env)
		return (clean_app(app), NULL);
	app->builtins = init_builtins();
	if (!app->builtins)
		return (clean_app(app), NULL);
	app->exit_status = 0;
	app->token = NULL;
	app->root = NULL;
	return (app);
}
