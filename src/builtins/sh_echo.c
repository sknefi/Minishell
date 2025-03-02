#include "../../include/minishell.h"

// Function to print the arguments passed to echo
int	sh_echo(t_app *app, t_token *token)
{
	token = token->next;
	while (token)
	{
		if (token->type == TOKEN_WORD_NVAR)
			p("%s", token->data);
		else if (token->type == TOKEN_WORD_VAR)
			p("%s", get_env_var(token->data + 1, app->env)); // + 1 to skip the '$' character
		token = token->next;
	}
	app->exit_status = 0;
	return (0);
}
