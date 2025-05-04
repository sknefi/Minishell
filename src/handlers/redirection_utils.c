#include "../../include/minishell.h"

/**
 * @brief Redirect stdout to the top file
 * @param node The node to redirect stdout to
 * @param saved_stdout The saved stdout file descriptor
 * @return 0 on success, 1 on failure
 */
static int redirect_stdout(t_ast_node *node, int saved_stdout)
{
	int	fd;

	if (node->type == NODE_REDIRECTION_OUT)
		fd = open(node->data[0], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else // NODE_APPEND
		fd = open(node->data[0], O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd < 0)
	{
		ft_printf(RED "Error: cannot open file %s\n" RST, node->data[0]);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
		return (1);
	}
	dup2(fd, STDOUT_FILENO); // redirect stdout to the top file
	close(fd);
	return (0);
}

t_ast_node	*find_command_node(t_ast_node *node)
{
	t_ast_node	*current;

	current = node;
	while (current && current->right && (current->right->type == NODE_REDIRECTION_OUT || current->right->type == NODE_APPEND))
		current = current->right;
	return (current->right); // the command node
}

int	create_files(t_ast_node *node, int saved_stdout)
{
	int			tmp_fd;
	t_ast_node	*current;

	if (redirect_stdout(node, saved_stdout))
		return (1);
	current = node->right;
	while (current && 
		(current->type == NODE_REDIRECTION_OUT || current->type == NODE_APPEND))
	{
		if (current->type == NODE_REDIRECTION_OUT)
			tmp_fd = open(current->data[0], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		else // NODE_APPEND
			tmp_fd = open(current->data[0], O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (tmp_fd < 0)
		{
			ft_printf(RED "Error: cannot open file %s\n" RST, current->data[0]);
			dup2(saved_stdout, STDOUT_FILENO);
			close(saved_stdout);
			return (1);
		}
		close(tmp_fd);
		current = current->right;
	}
	return (0);
}