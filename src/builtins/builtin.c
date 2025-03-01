#include "../../include/minishell.h"

int	exec_builtin(char *name, t_token *token, t_app *app)
{
	int			i;
	t_builtin	**builtins;

	i = 0;
	builtins = app->builtins;
	while (builtins[i])
	{
		if (ft_strcmp(builtins[i]->name, name) == 0)
			return (builtins[i]->f(app, token));
		i++;
	}
	return (EXIT_FAILURE);
}
