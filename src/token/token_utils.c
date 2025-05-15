/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmateja <tmateja@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:06:30 by tmateja           #+#    #+#             */
/*   Updated: 2025/05/04 19:15:48 by tmateja          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_token	*token_init(char *data, int type);

/*
 * Takes token head, data and type of new token.
 * Init token. Then iterate to find last token.
 * Appends token to token list.
 * Returns first token.
 */

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
	return (head);
}

/*
 * Takes data and type of new token.
 * Malloc memory for it.
 * Assigns type.
 * Assigns data by malloc it.
 * Returns token.
 */

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

/*
 * Takes token.
 * While there are tokens, it free memory allocated by
 * token_init().
 */

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

/*
 * Checks for space.
 */

int	ft_isspace(char c)
{
	if (c == 32)
		return (1);
	return (0);
}
