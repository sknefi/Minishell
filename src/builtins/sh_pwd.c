#include "../../include/minishell.h"

int	sh_pwd(t_app *app, char **av)
{
	p("%s\n", getcwd(NULL, 0));
	return (0);
}
