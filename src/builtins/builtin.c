#include "../../include/minishell.h"

/**
 * @brief Execute a builtin command
 * @return 0 on success, -1 on failure (malloc failed), 1 on failure (command not found)
*/
int	exec_builtin(t_app *app, t_token *token)
{
	int			i;
	char		*cmd_name;
	t_builtin	**builtins;

	i = 0;
	cmd_name = token->data;
	builtins = app->builtins;
	while (builtins[i])
	{
		if (ft_strcmp(builtins[i]->name, cmd_name) == 0)
			return (builtins[i]->f(app, token));
		i++;
	}
	return (1);
}
