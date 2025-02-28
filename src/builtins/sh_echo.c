#include "../../include/minishell.h"

// Function to print the arguments passed to echo
int		sh_echo(t_app *app, char **av)
{
	(void)app;
	(void)av;
	p("echo was called\n");
	return (0);
}