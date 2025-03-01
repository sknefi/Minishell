#include "../../include/minishell.h"

t_token	*token_append(t_token *head, int type, char *data)
{
	t_token	*last;
	t_token	*token;

	token = token_init(type, data);
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
	return (head);
}
