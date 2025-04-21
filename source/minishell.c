#include "minishell.h"
#include "structs.h"

void print_prefix(int depth, int is_last)
{
	for (int i = 0; i < depth - 1; i++)
		printf("│   ");
	if (depth > 0)
		printf("%s── ", is_last ? "└" : "├");
}

void print_ast_pretty(t_ast_node *node, int depth, int is_last)
{
	if (!node)
		return;

	print_prefix(depth, is_last);

	// Print node type
	switch (node->type)
	{
		case NODE_CMD:
			printf("CMD: ");
			if (node->data)
			{
				for (int i = 0; node->data[i]; i++)
					printf("%s ", node->data[i]);
			}
			printf("\n");
			break;
		case NODE_PIPE:
			printf("PIPE\n");
			break;
		case NODE_REDIRECTION_IN:
			printf("REDIR_IN: %s\n", node->data ? node->data[0] : "(null)");
			break;
		case NODE_REDIRECTION_OUT:
			printf("REDIR_OUT: %s\n", node->data ? node->data[0] : "(null)");
			break;
		case NODE_APPEND:
			printf("APPEND: %s\n", node->data ? node->data[0] : "(null)");
			break;
		case NODE_HEREDOC:
			printf("HEREDOC: %s\n", node->data ? node->data[0] : "(null)");
			break;
		default:
			printf("UNKNOWN NODE\n");
	}

	// Count children to determine how to draw tree lines
	int has_left = node->left != NULL;
	int has_right = node->right != NULL;

	if (has_left)
		print_ast_pretty(node->left, depth + 1, !has_right); // left is not last if there's a right
	if (has_right)
		print_ast_pretty(node->right, depth + 1, 1); // right is always last
}

/* ----- End of visualizer ----- */

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
		print_ast_pretty(root, 0, 1);
		tmp = token;
    	/*while (tmp)
    	{
        	printf("Token: %-10s | Typ: %d\n", tmp->data, tmp->type);
        	tmp = tmp->next;
    	} */
		free_tokens(token);
	}
	return (EXIT_SUCCESS);
}
