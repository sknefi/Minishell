#include "minishell.h"
#include <signal.h>

void	sig_handler()
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = handler();
	sigaction(SIGINT, &sa, NULL);
}
