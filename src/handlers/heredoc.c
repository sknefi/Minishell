#include "../../include/minishell.h"
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

#define HEREDOC_INPUT "> "

volatile int	g_heredoc;

/**
 * @brief Read a single line from heredoc prompt,
 * ensuring output goes to terminal
 * I love norminette
 * @param app The application (contains saved terminal stdout)
 * @return The input line (must be freed by caller), or NULL on EOF
 */
char    *read_heredoc_line(t_app *app)
{
    int		saved_stdout;
    char	*line;

    saved_stdout = dup(STDOUT_FILENO);
    if (app->term_stdout >= 0)
        dup2(app->term_stdout, STDOUT_FILENO);
    line = readline(HEREDOC_INPUT);
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdout);
	if (g_heredoc)
	{
		if (line)
			free(line);
		return (NULL);
	}
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
    char    	*line;
    t_input		input;

    setup_heredoc_signals();
    while (!g_heredoc)
    {
        line = read_heredoc_line(app);
		if (!line)
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
	if (g_heredoc)
	{
		write(1, "\n", 1);
		exit(130);
	}
	exit(0);
}

/**
 * @brief Handle heredoc redirection using a forked process
 * @param app The application
 * @param node The node to handle
 * @return 0 on success, 1 on failure
 */
int handle_heredoc(t_app *app, t_ast_node *node)
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

	// here starts parent process
	close(pipefd[1]); // we dont need to write into the pipe anymore

	// ignore both CTRL-C and CTRL-\ here
	// we make sure that the parent process ignores them so it wont kill the parent
	// process when the child process is running
	ignore_int_quit();

	if (waitpid(pid, &wstatus, 0) < 0)
		ft_printf("Error: waitpid");

	// we restore the main signals handlers for the parent process
	sig_handler();
	status = get_child_exit_status(wstatus);
	if (status != ES_SIG_NOT_USED)
		return (close(pipefd[0]), status);
	save_stdin = dup(STDIN_FILENO);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	status = exec_ast_node(node->right, app);
	dup2(save_stdin, STDIN_FILENO);
	close(save_stdin);
	return (status);
}
