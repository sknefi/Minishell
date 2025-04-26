#include "../../include/minishell.h"

/**
 * @brief Executes a command, itterate through the AST and execute the command, handle the redirections, pipes, heredocs, etc.
 * @param app The application
 * @return 0 on success, 1 on failure (command not found), -1 on failure (malloc failed)
*/
// int	sh_exec(t_app *app)
// {
// 	int		status;

// 	status = 1;
// 	if (token->type != TOKEN_COMMAND)
// 	{
// 		p(RED "bash: %s: command not found\n" RST, token->data);
// 		return (127);
// 	}
// 	status = exec_builtin(app, token);
// 	if (status != 1 || status == -1) // command is not a builtin or malloc failed
// 		return (status);
// 	// return (exec_external(app, token));
// 	return (0);
// }

void	sh_exec(t_app *app)
{
	int		status;
	t_ast_node	*node;

	node = app->root;
	if (!node)
		return ;

	if (node->type == NODE_PIPE)
	{
		// create pipe
		// fork left
		// in left child: redirect stdout to pipe write-end, close read-end, exec_ast(left)
		// fork right
		// in right child: redirect stdin to pipe read-end, close write-end, exec_ast(right)
		// in parent: wait for both
	}
	else if (node->type == NODE_REDIRECTION_IN)
	{
		// open the infile
		// dup2 to stdin
		// exec_ast(left)
	}
	else if (node->type == NODE_REDIRECTION_OUT)
	{
		// open outfile with O_TRUNC
		// dup2 to stdout
		// exec_ast(left)
	}
	else if (node->type == NODE_APPEND)
	{
		// open outfile with O_APPEND
		// dup2 to stdout
		// exec_ast(left)
	}
	else if (node->type == NODE_CMD)
	{
		status = exec_builtin(app, node->data);
		if (status != 1 || status == -1) // command is not a builtin or malloc failed
		{
			app->exit_status = status;
			return ;
		}
		// return (exec_external(app, token));
		app->exit_status = 0;
		return ;
	}
}
