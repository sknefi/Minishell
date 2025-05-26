/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkarika <fkarika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:23:24 by fkarika           #+#    #+#             */
/*   Updated: 2025/05/26 17:29:34 by fkarika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Read lines in a loop until delimiter or EOF
 * @param delimiter The string that ends the heredoc
 * @param pipe_write The write-end of the heredoc pipe
 * @param app Shell context
 */
static void	heredoc_read_loop(char *delimiter, int pipe_write, t_app *app)
{
	char		*line;
	t_input		input;

	while (!g_heredoc)
	{
		line = read_heredoc_line(app);
		if (!line)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		process_heredoc_line(line, &input, pipe_write, app);
	}
}

/**
 * @brief Child process to read heredoc input and write to pipe
 * @param delimiter The string that ends the heredoc
 * @param pipe_write The write-end of the heredoc pipe
 * @param app Shell context (used for terminal FD and word expansion)
 * @return Does not return - exits with status 0 on success, 130 on interrupt
 */
static void	heredoc_child_process(char *delimiter, int pipe_write, t_app *app)
{
	setup_heredoc_signals();
	heredoc_read_loop(delimiter, pipe_write, app);
	heredoc_child_cleanup(pipe_write, app);
}

/**
 * @brief Execute the right node of the heredoc
 * I love norminette
 */
static int	exec_ast_node_heredoc(t_ast_node *node, t_app *app,
	int pipe[2], int save_stdin)
{
	int	status;

	dup2(pipe[0], STDIN_FILENO);
	close(pipe[0]);
	status = exec_ast_node(node->right, app);
	dup2(save_stdin, STDIN_FILENO);
	close(save_stdin);
	return (status);
}

/**
 * @brief Handle heredoc redirection using a forked process
 * @param app The application
 * @param node The node to handle
 * @return 0 on success, 1 on failure
 */
int	handle_heredoc(t_app *app, t_ast_node *node)
{
	int		status;
	int		wstatus;
	int		pipefd[2];
	int		save_stdin;
	pid_t	pid;

	g_heredoc = 0;
	if (pipe(pipefd) < 0)
		return (ft_printf("Error: pipe"), 1);
	pid = fork();
	if (pid < 0)
		return (ft_printf("Error: fork"), close_pipe(pipefd), 1);
	if (pid == 0)
		heredoc_child_process(node->data[0], pipefd[1], app);
	close(pipefd[1]);
	ignore_int_quit();
	if (waitpid(pid, &wstatus, 0) < 0)
		ft_printf("Error: waitpid");
	sig_handler();
	status = get_child_exit_status(wstatus);
	if (status != ES_OK)
		return (close(pipefd[0]), status);
	save_stdin = dup(STDIN_FILENO);
	return (exec_ast_node_heredoc(node, app, pipefd, save_stdin));
}
