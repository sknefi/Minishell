#include "minishell.h"
#include "structs.h"
#include "token/token.h"

int	main(int argc, char **argv, char **env)
{
	t_token	*token;
	t_token	*tmp;
	(void)argc;
	(void)argv;
	(void)env;
	token = NULL;
	while (1)
	{
		lexer(&token);
		printf("juz po\n");
		printf("\n🔹 Lista Tokenów:\n");
		tmp = token;
    	while (tmp)
    	{
        	printf("Token: %-10s | Typ: %d\n", tmp->data, tmp->type);
        	tmp = tmp->next;
    	}
		free_tokens(token);
	}
	return (EXIT_SUCCESS);
}
