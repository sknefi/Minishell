#include "../../include/minishell.h"

// Function to change the current working directory
int	sh_cd(t_app *app, char **av)
{
	p("current working directory: %s\n", getcwd(NULL, 0));
	// change the current working directory to the path specified in av[1]
	if (chdir(av[1]) == -1)
	{
		p("cd: %s: No such file or directory\n", av[1]);
		app->exit_status = 1;
	}
	else
	{
		p("current working directory: %s\n", getcwd(NULL, 0));
		app->exit_status = 0;
	}
	return (0);
}
