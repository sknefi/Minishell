#include "../../include/minishell.h"

#define HEREDOC_INPUT "> "

/**
 * @brief Read input from heredoc and write to pipe
 * @param delimeter The delimiter to stop reading
 * @param pipe_write File descriptor to write to
 * @return 0 on success, 1 on failure
 */
static int read_heredoc_input(char *delimeter, int pipe_write)
{
	char *line;

	while (1)
	{
		line = readline(HEREDOC_INPUT);
		if (!line)
			break;
		if (ft_strcmp(line, delimeter) == 0)
		{
			free(line);
			break;
		}
		write(pipe_write, line, ft_strlen(line));
		write(pipe_write, "\n", 1);
		free(line);
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
	read_heredoc_input(node->data[0], pipefd[1]);
	close(pipefd[1]);
	saved_stdin = dup(STDIN_FILENO);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	status = exec_ast_node(node->right, app);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
	return (status);
}
