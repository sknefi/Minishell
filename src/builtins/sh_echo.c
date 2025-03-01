#include "../../include/minishell.h"

// Function to print the arguments passed to echo
int	sh_echo(t_app *app, t_token *token)
{
	(void)app;
	(void)token;
	p("echo was called\n");
	return (0);
}
