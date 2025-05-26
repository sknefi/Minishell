/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkarika <fkarika@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 20:47:33 by tmateja           #+#    #+#             */
/*   Updated: 2025/05/26 12:34:51 by fkarika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdlib.h>

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

/*
 * Builds AST command node.
 * It takes pointer to tokens.
 * First it eats all the redirections.
 * Then command_data is gathering and allocating data.
 * Creates cmd node.
 * If there is redirection chain, takes CMD token to rightmost node/leaf.
 * At the end it is trailing any redirections.
 * Returns t_ast_node on success, NULL on error.
 */

static t_ast_node	*ast_command(t_token **tokens)
{
	t_ast_node	*root;
	t_ast_node	*cmd;
	t_ast_node	*tmp_node;
	char		**data;

	root = NULL;
	while (*tokens && is_redir_token((*tokens)->type))
		root = parse_redirection(tokens, root);
	data = command_data(tokens);
	cmd = ast_new_node(NODE_CMD, data);
	if (root)
	{
		tmp_node = root;
		while (tmp_node->right)
			tmp_node = tmp_node->right;
		tmp_node->right = cmd;
	}
	else
		root = cmd;
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
