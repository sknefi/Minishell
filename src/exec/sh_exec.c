#include "../../include/minishell.h"

int	exec_ast_node(t_ast_node *node, t_app *app)
{
	int	status;

	if (!node)
		return (0);
	if (node->type == NODE_CMD)
	{
		status = exec_builtin(app, node->data);
		if (status == NOT_BUILTIN)
			status = exec_external(app, node->data);
		return (status);
	}
	else if (node->type == NODE_REDIRECTION_IN)
		return (handle_redirection_in(app, node));
	else if (node->type == NODE_REDIRECTION_OUT)
		return (handle_redirection_out(app, node));
	else if (node->type == NODE_APPEND)
		return (handle_redirection_out(app, node));
	else if (node->type == NODE_PIPE)
		return (handle_pipe(app, node));
	else if (node->type == NODE_HEREDOC)
		return (handle_heredoc(app, node));
	return (ES_ERROR);
}

int	sh_exec(t_app *app)
{
	int	status;

	if (!app->root)
		return (ES_ERROR);
	status = exec_ast_node(app->root, app);
	app->exit_status = status;
	return (status);
}
