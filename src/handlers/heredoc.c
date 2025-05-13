#include "../../include/minishell.h"

#define HEREDOC_INPUT "> "

int	handle_heredoc(t_app *app, t_ast_node *node)
{
	int		status;
	int		saved_stdin;
	int		pipefd[2];
	char	*line;
	char	*delimeter;

	if (pipe(pipefd) < 0)
		return (ft_printf(""), 1);
	delimeter = node->data[0];
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
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
    close(pipefd[1]);

    // Save stdin and redirect it from the pipe
    saved_stdin = dup(STDIN_FILENO);
    dup2(pipefd[0], STDIN_FILENO);
    close(pipefd[0]);

    // Execute the command
    status = exec_ast_node(node->right, app);

    // Restore stdin
    dup2(saved_stdin, STDIN_FILENO);
    close(saved_stdin);

    return status;
}
