/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmateja <tmateja@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 20:47:41 by tmateja           #+#    #+#             */
/*   Updated: 2025/05/09 20:48:06 by tmateja          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Takes type of AST node and data array it should contain.
 * Allocates memory for node.
 * Assigns type and data to it.
 * Left and right nodes are NULL.
 * Returns node.
 */

t_ast_node	*ast_new_node(t_node_types type, char **data)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

/*
 * Takes root node, type of node and data array.
 * If pipe, it connects left and right subtree.
 * If not pipe and no data, return NODE_CMD without args.
 * Then it recursive insert new node in right subtree.
 * Returns root node.
 */

t_ast_node	*ast_node_insert(t_ast_node *root, t_node_types type, char **data)
{
	t_ast_node	*node;

	if (!root)
		return (ast_new_node(type, data));
	if (NODE_PIPE == type)
	{
		node = ast_new_node(type, NULL);
		if (!node)
			return (NULL);
		node->left = root;
		node->right = NULL;
		if (!data)
			return (node);
	}
	else if (!data)
	{
		node = ast_new_node(NODE_CMD, data);
		return (node);
	}
	root->right = ast_node_insert(root->right, type, data);
	return (root);
}

/*
 * Norminette function.
 * Check for redirection type and creates new node.
 * If error, prints "Error\n" and return NULL.
 * Returns redirection_node.
 */

t_ast_node	*redirection_node(t_token *redir)
{
	t_ast_node	*redir_node;

	if (redir->type == TOKEN_REDIRECTION_IN)
		redir_node = ast_new_node(NODE_REDIRECTION_IN, NULL);
	else if (redir->type == TOKEN_REDIRECTION_OUT)
		redir_node = ast_new_node(NODE_REDIRECTION_OUT, NULL);
	else if (redir->type == TOKEN_APPEND)
		redir_node = ast_new_node(NODE_APPEND, NULL);
	else if (redir->type == TOKEN_HEREDOC)
		redir_node = ast_new_node(NODE_HEREDOC, NULL);
	else
	{
		ft_printf("Error\n");
		return (NULL);
	}
	return (redir_node);
}

/*
 * Takes root node.
 * Free all nodes, by going to the left and right.
 */

void	free_ast(t_ast_node *node)
{
	int	i;

	if (!node)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	if (node->data)
	{
		i = 0;
		while (node->data[i])
		{
			free(node->data[i]);
			i++;
		}
		free(node->data);
	}
	free(node);
}
