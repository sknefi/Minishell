#include "../../include/minishell.h"

t_token	*token_init(int type, char *data)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->data = ft_strdup(data);
	if (!token->data)
	{
		free(token);
		return (NULL);
	}
	token->next = NULL;
	token->prev = NULL;
	return (token);
}
