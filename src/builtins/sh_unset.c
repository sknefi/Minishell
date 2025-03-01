#include "../../include/minishell.h"

int	sh_unset(t_app *app, t_token *token)
{
	(void)app;
	(void)token;
	p("unset was called\n");
	return (0);
}
