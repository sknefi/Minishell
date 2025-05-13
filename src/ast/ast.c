/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmateja <tmateja@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 20:47:33 by tmateja           #+#    #+#             */
/*   Updated: 2025/05/13 18:27:44 by tmateja          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_ast_node	*handle_pipes(t_token **token);
static t_ast_node	*ast_command(t_token **tokens);
static t_ast_node	*parse_redirection(t_token **tokens, t_ast_node *cmd);
static t_ast_node	*ast_command_norminette(t_ast_node *cmd, \
	t_token **tokens, char **data);

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
		app->exit_status = 1; //change to ES_ERROR
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
 * It takes pointer to current token.
 * First counts how many TOKEN_WORD is it working with. (ls -la)(2)
 * Then allocates memory for it + NULL.
 * Then it fills data array with TOKEN_WORDs.
 * After it creates AST node NODE_CMD.
 * If redirections, parse it.
 */

static t_ast_node	*ast_command(t_token **tokens)
{
	char		**data;
	int			i;
	t_token		*tmp;
	t_ast_node	*cmd;

	i = 0;
	cmd = NULL;
	tmp = *tokens;
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
	cmd = ast_command_norminette(cmd, tokens, data);
	return (cmd);
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

/*
 * Function just for norminette purpose.
 * Takes cmd node, tokens and data to this token.
 * Also check for redirection.
 * Returns cmd node.
 */

static t_ast_node	*ast_command_norminette(t_ast_node *cmd, \
	t_token **tokens, char **data)
{
	cmd = ast_new_node(NODE_CMD, data);
	if (!cmd)
		return (NULL);
	while (*tokens && ((*tokens)->type == TOKEN_REDIRECTION_IN || \
		(*tokens)->type == TOKEN_REDIRECTION_OUT || \
		(*tokens)->type == TOKEN_APPEND || (*tokens)->type == TOKEN_HEREDOC))
		cmd = parse_redirection(tokens, cmd);
	if (!cmd)
		return (NULL);
	return (cmd);
}
