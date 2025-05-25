#include "../../include/minishell.h"

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
