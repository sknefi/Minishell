#include "minishell.h"
#include "structs.h"

/* ----- Visualizer ----- */

static void	print_prefix(int depth, int is_left)
{
	for (int i = 0; i < depth - 1; ++i)
		printf("│   ");
	if (depth > 0)
		printf("%s── ", is_left ? "├" : "└");
}

static const char *node_type_to_str(t_node_types type)
{
	switch (type)
	{
		case NODE_PIPE: return "PIPE";
		case NODE_REDIRECTION_IN: return "REDIR_IN (<)";
		case NODE_REDIRECTION_OUT: return "REDIR_OUT (>)";
		case NODE_APPEND: return "APPEND (>>)";
		case NODE_HEREDOC: return "HEREDOC (<<)";
		case NODE_CMD: return "CMD";
		default: return "UNKNOWN";
	}
}

static void	print_cmd_data(char **data)
{
	if (!data || !data[0])
		return;
	printf(": ");
	for (int i = 0; data[i]; i++)
		printf("%s%s", data[i], data[i + 1] ? " " : "");
}

void	print_ast(const t_ast_node *node, int depth, int is_left)
{
	if (!node)
	{
		print_prefix(depth, is_left);
		printf("[NULL]\n");
		return;
	}

	print_prefix(depth, is_left);
	printf("[%s", node_type_to_str(node->type));
	print_cmd_data(node->data);
	printf("]\n");

	if (!node->left && !node->right)
		return;
	
	// Recurse into children
	if (node->left)
		print_ast(node->left, depth + 1, 1);
	if (node->right)
		print_ast(node->right, depth + 1, 0);
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
	root = NULL;
	sig_handler();
	while (1)
	{
		if (prompt(&token))
		{
			free_tokens(token);
			continue ;
		}
		root = parse(token);
		if (!root)
		{
			free_tokens(token);
			free_ast(root);
			continue ;
		}
		print_ast(root, 0, 0);
		tmp = token;
    	while (tmp)
    	{
        	printf("Token: %-10s | Typ: %d\n", tmp->data, tmp->type);
        	tmp = tmp->next;
    	}
		//free_ast(root); //broken as in ast node's data are pointer to tokens
		free_tokens(token);
		printf("qwe\n");
	}
	return (EXIT_SUCCESS);
}
