#include "../../include/minishell.h"

int	sh_exit(t_app *app, char **av)
{
	(void)app;
	(void)av;
	p("exit was called\n");
	return (0);
}