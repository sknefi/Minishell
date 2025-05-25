#include "../../include/minishell.h"

/*
 * Norminette function.
 * Takes tokens.
 * It is gathering all the TOKEN_WORD and then
 * copying it into data.
 * Returns data on success, NULL on error.
 */

char	**command_data(t_token **tokens)
{
	char	**data;
	t_token	*tmp;
	size_t	i;

	tmp = *tokens;
	i = 0;
	while (tmp && tmp->type == TOKEN_WORD)
	{
		i++;
		tmp = tmp->next;
	}
	data = malloc(sizeof(char *) * (i + 1));
	if (!data)
		return (NULL);
	i = 0;
	while (*tokens && (*tokens)->type == TOKEN_WORD)
	{
		data[i++] = ft_strdup((*tokens)->data);
		*tokens = (*tokens)->next;
	}
	data[i] = NULL;
	return (data);
}

/*
 * Norminette function.
 * Check for redirection type and creates new node.
 * If error, prints "Error\n" and return NULL.
 * Returns redirection_node.
 */

t_node_types	redirection_type(t_token *redir)
{
	t_node_types	type;

	if (redir->type == TOKEN_REDIRECTION_IN)
		type = NODE_REDIRECTION_IN;
	else if (redir->type == TOKEN_REDIRECTION_OUT)
		type = NODE_REDIRECTION_OUT;
	else if (redir->type == TOKEN_APPEND)
		type = NODE_APPEND;
	else if (redir->type == TOKEN_HEREDOC)
		type = NODE_HEREDOC;
	else
	{
		ft_printf("Error\n");
		type = ERROR;
	}
	return (type);
}

/*
 * Takes tokens and type of redirection.
 * Returns data or NULL if error.
 */

char	**redirection_data(t_token **tokens)
{
	char	**data;

	data = malloc(2 * sizeof(char *));
	if (!data)
		return (NULL);
	data[0] = ft_strdup((*tokens)->data);
	data[1] = NULL;
	return (data);
}

// Norminette function.

int	is_redir_token(int	token_type)
{
	return (token_type == TOKEN_REDIRECTION_IN
			|| token_type == TOKEN_REDIRECTION_OUT
			|| token_type == TOKEN_APPEND
			|| token_type == TOKEN_HEREDOC);
}
