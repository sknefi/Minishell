#include "../../include/minishell.h"

/**
 * @brief Handle the left side of a pipe
 * @param app The application
 * @param node The AST node
 * @param pipefd The pipe file descriptors
 * @return Exit status (never returns in child process)
 */
static void	handle_left_child(t_app *app, t_ast_node *node, int *pipefd)
{
	int exit_status;
	
	close(pipefd[0]);
	if (dup2(pipefd[1], STDOUT_FILENO) < 0)
	{
		ft_printf(RED "Error: dup2 failed in left child\n" RST);
		close(pipefd[1]);
		clean_app(app);
		exit(EXIT_FAILURE);
	}
	close(pipefd[1]);
	exit_status = exec_ast_node(node->left, app);
	clean_app(app);
	exit(exit_status);
}

/**
 * @brief Handle the right side of a pipe
 * @param app The application
 * @param node The AST node
 * @param pipefd The pipe file descriptors
 * @return Exit status (never returns in child process)
 */
static void	handle_right_child(t_app *app, t_ast_node *node, int *pipefd)
{
	int exit_status;
	
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) < 0)
	{
		ft_printf(RED "Error: dup2 failed in right child\n" RST);
		close(pipefd[0]);
		clean_app(app);
		exit(EXIT_FAILURE);
	}
	close(pipefd[0]);
	exit_status = exec_ast_node(node->right, app);
	clean_app(app);
	exit(exit_status);
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

int	handle_pipe(t_app *app, t_ast_node *node)
{
	int		status;
	int		pipefd[2];
	pid_t	left_pid;
	pid_t	right_pid;

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
	{
		close_pipe(pipefd);
		waitpid(left_pid, NULL, 0); // Wait for left child to avoid zombie
		return (ft_printf(RED "Error: fork failed\n" RST), 1);
	}
	if (right_pid == 0)
		handle_right_child(app, node, pipefd);

	// Parent process: close pipes and wait for children
	close_pipe(pipefd);
	
	// Wait for both children to finish
	waitpid(left_pid, NULL, 0);
	waitpid(right_pid, &status, 0);
	
	return (WEXITSTATUS(status));
}
