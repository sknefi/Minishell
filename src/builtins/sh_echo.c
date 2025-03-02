#include "../../include/minishell.h"

static int	is_n_flag(char *arg)
{
	size_t	i;
	size_t	arg_len;

	arg_len = strlen(arg);
	if (arg_len <= 1 || arg[0] != '-')
		return (false);
	i = 1;
	while (i < arg_len)
	{
		if (arg[i] != 'n')
			return (false);
		i++;
	}
	return (true);	
}

// Function to print the arguments passed to echo
int	sh_echo(t_app *app, t_token *token)
{
	int		n_flag;

	n_flag = false;
	token = token->next;

	// handling only -n or -nnn or -nnnnn... options
	while (token && token->type == TOKEN_ARG)
	{
		if (!is_n_flag(token->data))
			break ;
		n_flag = true;
		token = token->next;
	}
	
	while (token)
	{
		if (token->type == TOKEN_WORD_NVAR)
			p("%s", token->data);
		else if (token->type == TOKEN_WORD_VAR)
			p("%s", get_env_var(token->data + 1, app->env)); // +1 to skip the '$' character
		if (token->next) // dont print space after the last argument
			p("_");
		token = token->next;
	}
	if (!n_flag)
		p("\n");
	app->exit_status = 0;
	return (0);
}
