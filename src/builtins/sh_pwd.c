#include "../../include/minishell.h"

int	sh_pwd(t_app *app, t_token *token)
{
	char	*cwd;

	(void)token;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		p("getcwd FAILED\n");
		app->exit_status = -1;
		return (-1);
	}
	p("%s\n", cwd);
	free(cwd);
	app->exit_status = 0;
	return (0);
}
