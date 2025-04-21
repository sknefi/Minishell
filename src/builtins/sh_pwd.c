#include "../../include/minishell.h"

int	sh_pwd(t_app *app, t_token *token)
{
	char	*cwd;

	(void)token;
	(void)app;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		p("getcwd FAILED\n");
		return (-1);
	}
	p("%s\n", cwd);
	free(cwd);
	return (0);
}
