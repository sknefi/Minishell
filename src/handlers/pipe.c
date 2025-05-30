/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkarika <fkarika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:23:33 by fkarika           #+#    #+#             */
/*   Updated: 2025/05/23 19:59:35 by fkarika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int	exit_status;

	close(pipefd[0]);
	if (dup2(pipefd[1], STDOUT_FILENO) < 0)
	{
		ft_printf("Error: dup2 failed in left child\n");
		close(pipefd[1]);
		clean_app(app);
		rl_clear_history();
		exit(EXIT_FAILURE);
	}
	close(pipefd[1]);
	exit_status = exec_ast_node(node->left, app);
	rl_clear_history();
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
	int	exit_status;

	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) < 0)
	{
		ft_printf("Error: dup2 failed in right child\n");
		close(pipefd[0]);
		clean_app(app);
		rl_clear_history();
		exit(EXIT_FAILURE);
	}
	close(pipefd[0]);
	exit_status = exec_ast_node(node->right, app);
	rl_clear_history();
	clean_app(app);
	exit(exit_status);
}

void	close_pipe(int *pipefd)
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
		return (ft_printf("Error: pipe creation failed\n"), 1);
	left_pid = fork();
	if (left_pid < 0)
		return (close_pipe(pipefd), ft_printf("Fork failed\n"), 1);
	if (left_pid == 0)
		handle_left_child(app, node, pipefd);
	right_pid = fork();
	if (right_pid < 0)
	{
		close_pipe(pipefd);
		waitpid(left_pid, NULL, 0);
		return (ft_printf("Error: fork failed\n"), 1);
	}
	if (right_pid == 0)
		handle_right_child(app, node, pipefd);
	close_pipe(pipefd);
	waitpid(left_pid, NULL, 0);
	waitpid(right_pid, &status, 0);
	return (get_child_exit_status(status));
}
