#include "../../include/minishell.h"

// Function to change the current working directory
int	sh_cd(t_app *app, char **av)
{
	(void)app;
	(void)av;
	p("cd was called\n");
	return (0);
}