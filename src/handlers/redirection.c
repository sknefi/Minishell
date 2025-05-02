#include "../../include/minishell.h"

/**
 * Type 1: > (truncate)
 * Type 2: >> (append)
 */
int	handle_redirection_out(t_app *app, t_ast_node *node, int type)
{
	int	fd;
	int	status;
	int	saved_stdout;

	if (type == 1)
		fd = open(node->data[0], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else // type == 2
		fd = open(node->data[0], O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd < 0)
	{
		ft_printf(RED "Error: cannot open file %s\n" RST, node->data[0]);
		return (1);
	}
	saved_stdout = dup(STDOUT_FILENO); // keep original stdout
	dup2(fd, STDOUT_FILENO); // redirect stdout to outfile
	close(fd);
	status = exec_ast_node(node->right, app);
	dup2(saved_stdout, STDOUT_FILENO); // restore original stdout
	close(saved_stdout);
	return (status);
}

/**
 * Handle input redirection (<)
 */
int	handle_redirection_in(t_app *app, t_ast_node *node)
{
	int	fd;
	int	status;
	int	saved_stdin;

	fd = open(node->data[0], O_RDONLY);
	if (fd < 0)
	{
		ft_printf(RED "Error: cannot open file %s\n" RST, node->data[0]);
		return (1);
	}
	saved_stdin = dup(STDIN_FILENO); // keep original stdin
	dup2(fd, STDIN_FILENO); // redirect stdin from infile
	close(fd);
	status = exec_ast_node(node->right, app);
	dup2(saved_stdin, STDIN_FILENO); // restore original stdin
	close(saved_stdin);
	return (status);
}


