#include "../../include/minishell.h"

// print token in format
// [TOKEN_TYPE] TOKEN_VALUE


/**
 * @brief Print token in format [TOKEN_TYPE] TOKEN_VALUE
*/
static char	*token_type_to_string(int type)
{
	if (type == TOKEN_COMMAND)
		return (ft_strdup("TOKEN_COMMAND"));
	else if (type == TOKEN_ARG)
		return (ft_strdup("TOKEN_ARG"));
	else if (type == TOKEN_PIPE)
		return (ft_strdup("TOKEN_PIPE"));
	else if (type == TOKEN_WORD_VAR)
		return (ft_strdup("TOKEN_WORD_VAR"));
	else if (type == TOKEN_WORD_NVAR)
		return (ft_strdup("TOKEN_WORD_NVAR"));
	else if (type == TOKEN_REDIRECTION)
		return (ft_strdup("TOKEN_REDIRECTION"));
	else if (type == TOKEN_FILE)
		return (ft_strdup("TOKEN_FILE"));
	else
		return (ft_strdup("TOKEN_UNKNOWN"));
}


void	token_print(t_token *token)
{
	char	*type;
	t_token	*temp;

	temp = token;
	p("\n\n");
	while (temp)
	{
		type = token_type_to_string(temp->type);
		printf("[%s] \t-> |%s|\n", type, temp->data);
		free(type);
		temp = temp->next;
	}
	p("\n");
}

void	token_print_inline(t_token *token)
{
	t_token	*temp;

	temp = token;
	while (temp)
	{
		printf("%s", temp->data);
		temp = temp->next;
	}
}