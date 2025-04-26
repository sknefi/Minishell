#include "../../include/minishell.h"

void	token_clean(t_token *head)
{
	t_token	*next;

	while (head)
	{
		next = head->next;
		free(head->data);
		free(head);
		head = next;
	}
}
