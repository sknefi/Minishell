#include "../../include/minishell.h"

#define HEREDOC_INPUT "> "

/**
 * @brief Read a single line from heredoc prompt,
 * ensuring output goes to terminal
 * @param app The application (contains saved terminal stdout)
 * @return The input line (must be freed by caller), or NULL on EOF
 */
char	*read_heredoc_line(t_app *app)
{
	int		saved_stdout;
	char	*line;

	saved_stdout = dup(STDOUT_FILENO);
	if (app->term_stdout >= 0)
		dup2(app->term_stdout, STDOUT_FILENO);
	line = readline(HEREDOC_INPUT);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
	return (line);
}

/**
 * @brief Read heredoc input and write to pipe until the delimiter is matched
 * @param delimiter The string that ends the heredoc
 * @param pipe_write The write-end of the heredoc pipe
 * @param app Shell context (used for terminal FD and word expansion)
 * @return 0 on success, 1 on failure
 */
int	read_heredoc_input(char *delimiter, int pipe_write, t_app *app)
{
	char	*line;
	t_input	input;

	while (1)
	{
		line = read_heredoc_line(app);
		if (!line)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		ft_memset(&input, 0, sizeof(t_input));
		input.line = ft_strdup(line);
		free(line);
		line = handle_word(&input, app);
		write(pipe_write, line, ft_strlen(line));
		write(pipe_write, "\n", 1);
		free(line);
		free(input.line);
	}
	return (0);
}

/**
 * @brief Handle heredoc redirection
 * @param app The application
 * @param node The node to handle
 * @return 0 on success, 1 on failure
 */
int	handle_heredoc(t_app *app, t_ast_node *node)
{
	int		status;
	int		pipefd[2];
	int		saved_stdin;

	if (pipe(pipefd) < 0)
		return (ft_printf(""), 1);
	read_heredoc_input(node->data[0], pipefd[1], app);
	close(pipefd[1]);
	saved_stdin = dup(STDIN_FILENO);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	status = exec_ast_node(node->right, app);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
	return (status);
}
