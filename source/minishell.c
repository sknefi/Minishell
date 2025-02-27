#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	char	*line;
	while (1)
	{
		lexer();
	}
	return (EXIT_SUCCESS);
}
