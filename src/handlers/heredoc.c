#include "../../include/minishell.h"

#define HEREDOC_INPUT "> "

/**
 * @brief Signal handler for heredoc mode
 * @param sig The signal number
 */
static void heredoc_signal_handler(int sig)
{
    if (sig == SIGINT || sig == SIGQUIT)
    {
        g_heredoc_interrupted = 1;
        close(STDIN_FILENO);  // Interrupt readline
    }
}
/**
 * @brief Set up signal handlers for heredoc mode
 */
static void    setup_heredoc_signals(void)
{
    struct sigaction    sa;

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = heredoc_signal_handler;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
}

/**
 * @brief Read a single line from heredoc prompt,
 * ensuring output goes to terminal
 * @param app The application (contains saved terminal stdout)
 * @return The input line (must be freed by caller), or NULL on EOF
 */
char    *read_heredoc_line(t_app *app)
{
    int        saved_stdout;
    char    *line;

    saved_stdout = dup(STDOUT_FILENO);
    if (app->term_stdout >= 0)
        dup2(app->term_stdout, STDOUT_FILENO);
    line = readline(HEREDOC_INPUT);
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdout);
    return (line);
}

/**
 * @brief Child process to read heredoc input and write to pipe
 * @param delimiter The string that ends the heredoc
 * @param pipe_write The write-end of the heredoc pipe
 * @param app Shell context (used for terminal FD and word expansion)
 * @return Does not return - exits with status 0 on success, 130 on interrupt
 */
static void    heredoc_child_process(char *delimiter, int pipe_write, t_app *app)
{
    char    *line;
    t_input    input;

    g_heredoc_interrupted = 0;
    setup_heredoc_signals();
    while (!g_heredoc_interrupted)
    {
        line = read_heredoc_line(app);
        if (!line || g_heredoc_interrupted)
        {
            free(line);
            break;
        }
        if (ft_strcmp(line, delimiter) == 0)
        {
            free(line);
            break;
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
    close(pipe_write);
	rl_clear_history();
	clean_app(app);
    exit(g_heredoc_interrupted ? 130 : 0);
}

/**
 * @brief Handle heredoc redirection using a forked process
 * @param app The application
 * @param node The node to handle
 * @return 0 on success, 1 on failure
 */
int handle_heredoc(t_app *app, t_ast_node *node)
{
	int     pipefd[2];
	int     saved_stdin;
	pid_t   pid;
	int     wstatus = 0;
	int     status;

	if (pipe(pipefd) < 0)
		return (ft_printf("Pipe error\n"), 1);

	pid = fork();
	if (pid < 0)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return (ft_printf("Fork error\n"), 1);
	}

	if (pid == 0)
		heredoc_child_process(node->data[0], pipefd[1], app);

	// Parent process
	close(pipefd[1]);

	if (waitpid(pid, &wstatus, 0) < 0)
	{
		close(pipefd[0]);
		app->exit_status = 1;
		return (1);
	}

	// If heredoc was interrupted (Ctrl+C), skip execution
	if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) == 130)
	{
		close(pipefd[0]);
        g_heredoc_interrupted = 0;
		return (130);  // Skip running the actual command
	}

	// Execute the right side of the heredoc
	saved_stdin = dup(STDIN_FILENO);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);

	status = exec_ast_node(node->right, app);

	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);

	return (status);
}

