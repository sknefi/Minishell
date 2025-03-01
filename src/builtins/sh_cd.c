#include "../../include/minishell.h"

// Function to change the current working directory
int	sh_cd(t_app *app, t_token *token)
{
	// get i-th token or NULL if i-th token does not exist or i out of range
	p("current working directory: %s\n", getcwd(NULL, 0));
	// change the current working directory to the path specified in the next token
	if (chdir(token->next->data) == -1)
	{
		p("cd: %s: No such file or directory\n", token->next->data);
		app->exit_status = 1;
	}
	else
	{
		p("current working directory: %s\n", getcwd(NULL, 0));
		app->exit_status = 0;
	}
	return (0);
}
