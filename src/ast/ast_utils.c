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

static char	*read_heredoc(const char *del);

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

t_node_types	redirection_type(t_token *redir)
{
	t_node_types	type;

	if (redir->type == TOKEN_REDIRECTION_IN)
		type = NODE_REDIRECTION_IN;
	else if (redir->type == TOKEN_REDIRECTION_OUT)
		type = NODE_REDIRECTION_OUT;
	else if (redir->type == TOKEN_APPEND)
		type = NODE_APPEND;
	else if (redir->type == TOKEN_HEREDOC)
		type = NODE_HEREDOC;
	else
	{
		ft_printf("Error\n");
		type = ERROR;
	}
	return (type);
}

/*
 * Takes tokens and type of redirection.
 * if Heredoc, it will read as long as we type del, which is "<< del"
 * Returns data or NULL if error.
 */

char	**redirection_data(t_token **tokens, t_node_types type)
{
	char	**data;
	char	*del;
	char	*heredoc_data;

	if (NODE_HEREDOC == type)
	{
		del = ft_strdup((*tokens)->data);
		if (!del)
			return (NULL);
		heredoc_data = read_heredoc(del);
		if (!heredoc_data)
			return (NULL);
		data = malloc(3 * sizeof(char *));
		data[0] = del;
		data[1] = heredoc_data;
		data[2] = NULL;
	}
	else
	{
		data = malloc(2 * sizeof(char *));
		data[0] = ft_strdup((*tokens)->data);
		data[1] = NULL;
	}

	return (data);
}

/*
 * Takes del as parameter.
 * Read until Ctrl + D or del is detected.
 * Returns result as string, with \n or NULL on error.
 */

static char	*read_heredoc(const char *del)
{
	char	*result;
	char	*line;
	char	*tmp;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, del) == 0)
		{
			free(line);
			break ;
		}
		tmp = result;
		result = ft_strjoin(result, line);
		free(tmp);
		tmp = result;
		result = ft_strjoin(result, "\n");
		free(tmp);
		free(line);
	}
	return (result);
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
