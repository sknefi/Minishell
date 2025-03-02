#include "../../include/minishell.h"

// Function to exit the shell
int	sh_exit(t_app *app, t_token *token)
{
	(void)app;
	(void)token;
	exit(EXIT_SUCCESS);
	return (0);
}
