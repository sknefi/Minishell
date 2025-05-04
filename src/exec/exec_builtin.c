#include "../../include/minishell.h"

/**
 * @brief Execute a builtin command
 * @return 0 on success, 
 * -1 on failure (malloc failed), 
 * 1 command valid but error - too many arguments
 * 2 command is not a builtin 
*/
int	exec_builtin(t_app *app, char **cmd_args)
{
	int			i;
	char		*cmd_name;
	t_builtin	**builtins;

	i = 0;
	cmd_name = cmd_args[0];
	builtins = app->builtins;
	while (builtins[i])
	{
		if (ft_strcmp(builtins[i]->name, cmd_name) == 0)
			return (builtins[i]->f(app, cmd_args));
		i++;
	}
	return (2); // command is not a builtin
}
