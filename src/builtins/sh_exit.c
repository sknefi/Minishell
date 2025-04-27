#include "../../include/minishell.h"

// Function to exit the shell
int	sh_exit(t_app *app, char **cmd_args)
{
	(void)app;
	(void)cmd_args;
	clean_app(app);
	p(RED "exiting minishell\n" RST);
	exit(EXIT_SUCCESS);
	return (0);
}
