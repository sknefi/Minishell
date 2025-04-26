#include "../../include/minishell.h"

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

t_ast_node	*ast_node_insert(t_ast_node *root, t_node_types type, char **data)
{
	t_ast_node	*node;

	if (!root)
		return (ast_new_node(type, data));
	if (NODE_PIPE == type)
	{
		node = ast_new_node(type, NULL);
		node->left = root;
		node->right = NULL;
	}
	if (!data)
	{
		node->right = ast_new_node(NODE_CMD, data);
		return (node);
	}
	root->right = ast_node_insert(root->right, type, data);
	return (root);
}

void	free_ast(t_ast_node *node)
{
	int	i;

	i = 0;
	if (!node)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	if (node->data)
	{
		while (node->data[i])
		{
			free(node->data[i]);
			i++;
		}
		//free(node->data);
	}
	free(node);
}
