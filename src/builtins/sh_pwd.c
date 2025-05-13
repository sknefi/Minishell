#include "../../include/minishell.h"

int	sh_pwd(t_app *app, char **cmd_args)
{
	char	*cwd;

	(void)app;
	(void)cmd_args;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_printf("getcwd FAILED\n");
		return (ES_FAILED);
	}
	ft_printf("%s\n", cwd);
	free(cwd);
	return (ES_OK);
}
