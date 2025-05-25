/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmateja <tmateja@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 20:47:41 by tmateja           #+#    #+#             */
/*   Updated: 2025/05/13 18:05:06 by tmateja          ###   ########.fr       */
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
