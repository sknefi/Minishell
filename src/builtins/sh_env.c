#include "../../include/minishell.h"

int	sh_env(t_app *app, char **av)
{
	int		i;

	(void)av;
	i = 0;
	while (app->env[i])
	{
		p("%s\n", app->env[i]);
		i++;
	}
	app->exit_status = 0;
	return (0);
}
