#include "../minishell.h"

//void	tokenization(char *line);

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
		//tokenization(line);
	}
	free(line);
	rl_clear_history();
	exit(EXIT_FAILURE);

}

/* void	tokenization(char *line)
{
	while (*line)
	{
		while (*line && ft_isspace(*line))
			line++;
		if (!(*line))
			// TODO
} */
