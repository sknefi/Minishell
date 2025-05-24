/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkarika <fkarika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 20:47:33 by tmateja           #+#    #+#             */
/*   Updated: 2025/05/24 21:52:55 by fkarika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_ast_node	*handle_pipes(t_token **token);
static t_ast_node	*ast_command(t_token **tokens);
static t_ast_node	*parse_redirection(t_token **tokens, t_ast_node *cmd);

/*
 * Main ast function, which takes tokens and returns root node
 * if everytihng was successful or NULL when error.
 */

t_ast_node	*parse(t_token *tokens, t_app *app)
{
	t_ast_node	*root;

	root = handle_pipes(&tokens);
	if (!root)
	{
		app->exit_status = ES_ERROR;
		return (NULL);
	}
	return (root);
}

/*
 * Takes pointer to current token.
 * First token is always command node.
 * Continue looping as long as token is pipe.
 * Right node is also a command node.
 * So, if pipe token, it creates NODE_PIPE.
 * On the left it assigns left node and put right node as a command node.
 * Returns pointer to the root of AST tree segment.
 */

static t_ast_node	*handle_pipes(t_token **tokens)
{
	t_ast_node	*left;
	t_ast_node	*right;

	left = ast_command(tokens);
	if (!left)
		return (NULL);
	while (*tokens && (*tokens)->type == TOKEN_PIPE)
	{
		*tokens = (*tokens)->next;
		right = ast_command(tokens);
		if (!right)
			return (NULL);
		left = ast_node_insert(left, NODE_PIPE, NULL);
		if (!left)
			return (NULL);
		left->right = right;
	}
	return (left);
}


static inline int is_redir_token(int tokentype)
{
	return (tokentype == TOKEN_REDIRECTION_IN
		|| tokentype == TOKEN_REDIRECTION_OUT
		|| tokentype == TOKEN_APPEND
		|| tokentype == TOKEN_HEREDOC);
}
	
/*
* Builds AST command node.
* It takes pointer to current token.
* First counts how many TOKEN_WORD is it working with. (ls -la)(2)
* Then allocates memory for it + NULL.
* Then it fills data array with TOKEN_WORDs.
* After it creates AST node NODE_CMD.
* If redirections, parse it.
*/
static t_ast_node *ast_command(t_token **tokens)
{
	t_ast_node *root = NULL;
	char **data;
	int    i;

	// 1) eat any leading redirections first
	while (*tokens && is_redir_token((*tokens)->type))
		root = parse_redirection(tokens, root);

	// 2) now count _all_ the WORD tokens (your actual command + args)
	i = 0;
	for (t_token *t = *tokens;
			t && t->type == TOKEN_WORD;
			t = t->next)
		++i;

	// 3) copy them into data[]
	data = malloc((i+1)*sizeof *data);
	if (!data) return NULL;
	for (int j = 0;  j < i;  ++j)
	{
		data[j] = ft_strdup((*tokens)->data);
		*tokens   = (*tokens)->next;
	}
	data[i] = NULL;

	// 4) build your CMD node  
	t_ast_node *cmd = ast_new_node(NODE_CMD, data);

	// 5) if we had a leading‐redir chain, tack this CMD onto its rightmost leaf
	if (root)
	{
		t_ast_node *r = root;
		while (r->right) r = r->right;
		r->right = cmd;
	}
	else
		root = cmd;

	// 6) now eat & attach any trailing redirections
	while (*tokens && is_redir_token((*tokens)->type))
		root = parse_redirection(tokens, root);
	if (!root)
		return (free_ast(cmd), NULL);
	return (root);
}


/*
 * Takes pointer to current token and cmd node.
 * Saves redirection in redir.
 * Moving to the next, it checks syntax.
 * Then it creates redirection node depending on redirection;
 * type gets from redirection_type() and data from redirection_data().
 * Cmd node is stored at the right.
 * Returns redirection node.
 */

static t_ast_node	*parse_redirection(t_token **tokens, t_ast_node *cmd)
{
	char			**data;
	t_token			*redir;
	t_ast_node		*redir_node;
	t_node_types	type;

	redir = *tokens;
	*tokens = (*tokens)->next;
	if (!*tokens || (*tokens)->type != TOKEN_WORD)
	{
		ft_printf("Error\n");
		return (NULL);
	}
	type = redirection_type(redir);
	if (ERROR == type)
		return (NULL);
	data = redirection_data(tokens);
	if (!data)
		return (NULL);
	redir_node = ast_new_node(type, data);
	redir_node->right = cmd;
	*tokens = (*tokens)->next;
	return (redir_node);
}

