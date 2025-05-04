#include "../../include/minishell.h"

static int	exec_ast_node(t_ast_node *node, t_app *app)
{
	int	status;
	int	fd;

	if (!node)
		return (0);

	if (node->type == NODE_CMD)
	{
		// -1 - malloc failed
		//  0 - success
		//  1 - too many arguments
		//  2 - command is not a builtin
		status = exec_builtin(app, node->data);
		if (status == 2) // command is not a builtin
			status = exec_external(app, node->data);
		return (status);
	}
	else if (node->type == NODE_REDIRECTION_IN)
	{
		// open the infile
		if (!node->data || !node->data[0])
			return (1);
		fd = open(node->data[0], O_RDONLY);
		if (fd < 0)
		{
			ft_printf(RED "Error: cannot open file %s\n" RST, node->data[0]);
			return (1);
		}
		// dup2 to stdin
		dup2(fd, STDIN_FILENO);
		close(fd);
		// exec_ast(left)
		return (exec_ast_node(node->right, app));
	}
	else if (node->type == NODE_REDIRECTION_OUT)
	{
		// open outfile with O_TRUNC
		if (!node->data || !node->data[0])
			return (1);
		fd = open(node->data[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			ft_printf(RED "Error: cannot open file %s\n" RST, node->data[0]);
			return (1);
		}
		// dup2 to stdout
		dup2(fd, STDOUT_FILENO);
		close(fd);
		// exec_ast(left)
		return (exec_ast_node(node->right, app));
	}
	else if (node->type == NODE_APPEND)
	{
		// open outfile with O_APPEND
		if (!node->data || !node->data[0])
			return (1);
		fd = open(node->data[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
		{
			ft_printf(RED "Error: cannot open file %s\n" RST, node->data[0]);
			return (1);
		}
		// dup2 to stdout
		dup2(fd, STDOUT_FILENO);
		close(fd);
		// exec_ast(left)
		return (exec_ast_node(node->right, app));
	}
	else if (node->type == NODE_PIPE)
	{
		// create pipe
		int pipefd[2];
		if (pipe(pipefd) < 0)
		{
			ft_printf(RED "Error: pipe creation failed\n" RST);
			return (1);
		}

		// fork left
		pid_t left_pid = fork();
		if (left_pid < 0)
		{
			close(pipefd[0]);
			close(pipefd[1]);
			return (1);
		}

		if (left_pid == 0)
		{
			// in left child: redirect stdout to pipe write-end, close read-end, exec_ast(left)
			close(pipefd[0]);
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[1]);
			exit(exec_ast_node(node->left, app));
		}

		// fork right
		pid_t right_pid = fork();
		if (right_pid < 0)
		{
			close(pipefd[0]);
			close(pipefd[1]);
			return (1);
		}

		if (right_pid == 0)
		{
			// in right child: redirect stdin to pipe read-end, close write-end, exec_ast(right)
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
			exit(exec_ast_node(node->right, app));
		}

		// in parent: wait for both
		close(pipefd[0]);
		close(pipefd[1]);
		waitpid(left_pid, &status, 0);
		waitpid(right_pid, &status, 0);
		return (WEXITSTATUS(status));
	}
	return (0);
}

int	sh_exec(t_app *app)
{
	int		status;
	t_ast_node	*node;

	node = app->root;
	if (!node)
		return (0);

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
		// -1 - malloc failed
		//  0 - success
		//  1 - too many arguments
		//  2 - command is not a builtin
		status = exec_builtin(app, node->data);
		if (status == 2) // command is not a builtin
			status = exec_external(app, node->data);
		ft_printf("status: %d\n", status);
		app->exit_status = status;
		return (status);
	}
	return (0);
}