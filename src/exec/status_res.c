#include "../../include/minishell.h"

int	get_child_exit_status(int status)
{
	int	sig;

	if (WIFEXITED(status))
		return WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			return (ES_EXIT);
		if (sig == SIGQUIT)
			return (ES_SIGQUIT);
	}
	return (ES_SIG_NOT_USED);
}
