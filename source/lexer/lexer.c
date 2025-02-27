#include "../minishell.h"

void	lexer(void)
{
	char	*line;

	line = NULL;
	line = readline("minishell> ");
	if (!line)
		exit(EXIT_FAILURE);
	if (*line)
		add_history(line);
	free(line);
	rl_clear_history();
	exit(EXIT_FAILURE);

}
