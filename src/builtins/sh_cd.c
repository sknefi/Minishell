#include "../../include/minishell.h"



// Function to change the current working directory
int	sh_cd(t_app *app, t_token *token)
{
	char	*path;

	(void)token;
	//TESTING
	if (sh_pwd(app, token) == -1)
		return (-1);
	//END TESTING

	if (!token->next)
		path = get_env_var("HOME", app->env);
	else
		path = token->next->data;
	if (chdir(path) == -1)
	{
		p(RED "cd: %s: No such file or directory\n" RST, token->next->data);
		app->exit_status = 1;
	}

	//TESTING
	// the exit status of cd is now comming from pwd - because of this test
	if (sh_pwd(app, token) == -1)
		return (-1);
	//END TESTING

	return (0);
}
