#include "../../include/minishell.h"

int	sh_export(t_app *app, char **av)
{
	(void)app;
	(void)av;
	p("export was called\n");
	return (0);
}
