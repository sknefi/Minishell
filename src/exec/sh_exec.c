#include "../../include/minishell.h"

/**
 * @brief Executes a command
 * @param app The application
 * @param token The token
 * @return 0 on success, 1 on failure (command not found), -1 on failure (malloc failed)
*/
int	sh_exec(t_app *app, t_token *token)
{
	int		status;

	status = 1;
	if (token->type != TOKEN_COMMAND)
	{
		p(RED "bash: %s: command not found\n" RST, token->data);
		return (127);
	}
	status = exec_builtin(app, token);
	if (status != 1 || status == -1) // command is not a builtin or malloc failed
		return (status);
	// return (exec_external(app, token));
	return (0);
}
