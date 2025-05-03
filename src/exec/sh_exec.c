#include "../../include/minishell.h"

// -1 - malloc failed
//  0 - success
//  1 - too many arguments
//  2 - command is not a builtin
int	exec_ast_node(t_ast_node *node, t_app *app)
{
	int	status;

	if (!node)
		return (0);
	if (node->type == NODE_CMD)
	{
		status = exec_builtin(app, node->data);
		if (status == 2) // command is not a builtin
			status = exec_external(app, node->data);
		return (status);
	}
	else if (node->type == NODE_REDIRECTION_IN)
		return (handle_redirection_in(app, node));
	else if (node->type == NODE_REDIRECTION_OUT)
		return (handle_redirection_out(app, node, 1));
	else if (node->type == NODE_APPEND)
		return (handle_redirection_out(app, node, 2));
	else if (node->type == NODE_PIPE)
	{
		// create pipe
		// fork left
		// in left child: redirect stdout to pipe write-end, close read-end, exec_ast(left)
		// fork right
		// in right child: redirect stdin to pipe read-end, close write-end, exec_ast(right)
		// in parent: wait for both
	}
	return (0);
}

int	sh_exec(t_app *app)
{
	int status;

	if (!app->root)
		return (0);
	status = exec_ast_node(app->root, app);
	app->exit_status = status;
	return (status);
}