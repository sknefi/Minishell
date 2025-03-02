#include "../minishell.h"

static t_token	*token_init(char *data, int type);

t_token	*token_append(t_token *head, char *data, int type)
{
	t_token	*last;
	t_token	*token;

	token = token_init(data, type);
	if (!token)
		return (NULL);
	if (!head)
		return (token);
	last = head;
	while (last->next)
		last = last->next;
	last->next = token;
	token->prev = last;
	token->next = NULL;
	return (token);
}

static t_token	*token_init(char *data, int type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
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

void	free_tokens(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token;
		token = token->next;
		free(tmp->data);
		free(tmp);
	}
}
