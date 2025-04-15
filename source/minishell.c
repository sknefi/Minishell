#include "minishell.h"
#include "structs.h"

int	main(int argc, char **argv, char **env)
{
	t_token	*token;
	t_ast_node	*root;
	t_token *tmp;

	(void)argc;
	(void)argv;
	(void)env;
	token = NULL;
	sig_handler();
	while (1)
	{
		prompt(&token);
		printf("juz po\n");
		root = parse(token);
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
