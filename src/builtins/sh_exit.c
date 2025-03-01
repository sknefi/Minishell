#include "../../include/minishell.h"

int	sh_exit(t_app *app, t_token *token)
{
	(void)app;
	(void)token;
	p("exit was called\n");
	return (0);
}
