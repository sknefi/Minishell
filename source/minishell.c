#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	while (1)
	{
		lexer();
		printf("juz po\n");
	}
	return (EXIT_SUCCESS);
}
