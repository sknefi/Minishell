#include "minishell.h"
#include <signal.h>
#include <unistd.h>

static void	sigint_handler(int sig);
static void	sigquit_handler(int sig);

void	sig_handler()
{
	struct sigaction	sa;

	// Handle SIGINT
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = sigint_handler;
	sigaction(SIGINT, &sa, NULL);

	//Handle SIGQUIT
	sa.sa_handler = sigquit_handler;
	sigaction(SIGQUIT, &sa, NULL);
}

//TODO error codes

static void	sigint_handler(int sig)
{
	(void)sig;

	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	sigquit_handler(int sig)
{
	(void)sig;
	//TODO
}
