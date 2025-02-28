#include "../minishell.h"

void	tokenization(t_token	*token);

void	lexer(void)
{
	char	*line;

	line = NULL;
	line = readline("minishell> ");
	if (!line)
		exit(EXIT_FAILURE);
	if (*line)
	{
		add_history(line);
		tokenization(line);
	}
	free(line);
	rl_clear_history();
	exit(EXIT_FAILURE);

}

void	tokenization(t_token	*token);
