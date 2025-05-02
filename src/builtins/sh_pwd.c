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
		return (-1);
	}
	ft_printf("%s\n", cwd);
	free(cwd);
	return (0);
}
