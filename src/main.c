/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkarika <fkarika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:13:05 by tmateja           #+#    #+#             */
/*   Updated: 2025/05/23 20:23:18 by fkarika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

static int	shell_loop(t_app *app, int helper);

int	main(int argc, char **argv, char **env)
{
	t_app		*app;
	int			helper;

	(void)argc;
	(void)argv;
	app = init_app(env);
	if (!app)
		return (clean_app(app), EXIT_FAILURE);
	helper = 0;
	sig_handler();
	if (shell_loop(app, helper))
		return (clean_app(app), EXIT_FAILURE);
	clean_app(app);
	return (0);
}

static int	shell_loop(t_app *app, int helper)
{
	while (1)
	{
		helper = prompt(app, app->input);
		if (helper == 1)
		{
			free_tokens(app->token);
			continue ;
		}
		else if (helper == -1)
			return (1);
		app->exit_status = helper;
		app->root = parse(app->token, app);
		// print_ast_pretty(app->root, 0, 1); // Print the AST in a pretty format
		if (!app->root)
		{
			free(app->input->line);
			free_ast(app->root);
			free_tokens(app->token);
			continue ;
		}
		sh_exec(app);
		free_ast(app->root);
		free_tokens(app->token);
		
		app->root = NULL;
	}
}
