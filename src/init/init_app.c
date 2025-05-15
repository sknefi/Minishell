#include "../../include/minishell.h"

void	clean_app(t_app *app)
{
	if (app)
	{
		free_env(app->env);
		free_builtins(app->builtins);
		free_tokens(app->token);
		free_ast(app->root);
		if (app->input->line)
			free(app->input->line);
		if (app->input)
			free(app->input);
		free(app);
	}
}

t_app	*init_app(char **env)
{
	t_app	*app;

	app = (t_app *)malloc(sizeof(t_app));
	if (!app)
		return (NULL);
	app->input = (t_input *)malloc(sizeof(t_input));
	if (!app->input)
		return (NULL);
	app->env = init_env(env);
	if (!app->env)
		return (NULL);
	app->builtins = init_builtins();
	if (!app->builtins)
		return (NULL);
	app->exit_status = 0;
	app->token = NULL;
	app->root = NULL;
	return (app);
}
