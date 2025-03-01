#include "../../include/minishell.h"

int	sh_pwd(t_app *app, t_token *token)
{
	(void)app;
	(void)token;
	p("%s\n", getcwd(NULL, 0));
	return (0);
}
