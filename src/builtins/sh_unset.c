#include "../../include/minishell.h"

int	sh_unset(t_app *app, char **av)
{
	(void)app;
	(void)av;
	p("unset was called\n");
	return (0);
}