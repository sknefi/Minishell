#include "../../include/minishell.h"

/**
 * @brief Handle the left side of a pipe
 * @param app The application
 * @param node The AST node
 * @param pipefd The pipe file descriptors
 * @return Exit status (never returns in child process)
 */
static void handle_left_child(t_app *app, t_ast_node *node, int *pipefd)
{
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	exit(exec_ast_node(node->left, app));
}

/**
 * @brief Handle the right side of a pipe
 * @param app The application
 * @param node The AST node
 * @param pipefd The pipe file descriptors
 * @return Exit status (never returns in child process)
 */
static void handle_right_child(t_app *app, t_ast_node *node, int *pipefd)
{
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	exit(exec_ast_node(node->right, app));
}

/**
 * @brief Close the pipe
 * @param pipefd The pipe file descriptors
 */
static void	close_pipe(int *pipefd)
{
	close(pipefd[0]);
	close(pipefd[1]);
}

int handle_pipe(t_app *app, t_ast_node *node)
{
	int pipefd[2];
	int status;
	pid_t left_pid, right_pid;
	
	if (pipe(pipefd) < 0)
		return (ft_printf(RED "Error: pipe creation failed\n" RST), 1);

	// Fork left child
	left_pid = fork();
	if (left_pid < 0)
		return (close_pipe(pipefd), ft_printf(RED "Error: fork failed\n" RST), 1);
	if (left_pid == 0)
		handle_left_child(app, node, pipefd);

	// Fork right child
	right_pid = fork();
	if (right_pid < 0)
		return (close_pipe(pipefd), ft_printf(RED "Error: fork failed\n" RST), 1);
	if (right_pid == 0)
		handle_right_child(app, node, pipefd);

	// Parent process: close pipes and wait for children
	close_pipe(pipefd);
	waitpid(left_pid, &status, 0);
	waitpid(right_pid, &status, 0);
	return (WEXITSTATUS(status));
}
