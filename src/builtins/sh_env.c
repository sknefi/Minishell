#include "../../include/minishell.h"

int	sh_env(t_app *app, t_token *token)
{
	int		i;

	(void)token;
	i = 0;
	while (app->env[i])
	{
		p("%s\n", app->env[i]);
		i++;
	}
	app->exit_status = 0;
	return (0);
}
