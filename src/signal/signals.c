#include "../../include/minishell.h"

static void	sigint_handler(int sig);
// static void	sigquit_handler(int sig);

void	sig_handler()
{
	struct sigaction	sa;

	// Handle SIGINT
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = sigint_handler;
	sigaction(SIGINT, &sa, NULL);

	//Handle SIGQUIT
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

//TODO error codes

static void	sigint_handler(int sig)
{
	(void)sig;

	write(STDOUT_FILENO, "^C\n", 3);
}

// static void	sigquit_handler(int sig)
// {
// 	(void)sig;
// 	//TODO
// }
