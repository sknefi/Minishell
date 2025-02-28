#include "../../include/minishell.h"

int	sh_pwd(t_app *app, char **av)
{
	(void)app;
	(void)av;
	p("pwd was called\n");
	return (0);
}