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

	// set n_flag to true if there is -n flag
	// and break the loop if there is no more ARGS
	while (token)
	{
		if (is_n_flag(token->data))
			n_flag = true;
		if (token->type != TOKEN_ARG)
			break;
		token = token->next;
	}

	// all ARGS has to be after echo
	// when I iterate through the tokens, when ARGS are finished, I am starting to print 
	// everything else till I find redirect or pipe
	while (token)
	{
		if (token->type == TOKEN_WORD_VAR)
			p("%s", get_env_var(token->data + 1, app->env)); // +1 to skip the '$' character
		else if (token->type != TOKEN_REDIRECTION && token->type != TOKEN_PIPE)
			p("%s", token->data);
		if (token->next) // dont print space after the last argument
			p("_");
		token = token->next;
	}
	if (!n_flag)
		p("\n");
	return (0);
}
