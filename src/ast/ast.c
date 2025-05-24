#include "../../include/minishell.h"

static t_ast_node	*handle_pipes(t_token **token);
static t_ast_node	*ast_command(t_token **tokens);

t_ast_node	*parse(t_token *tokens, t_app *app)
{
	t_ast_node	*root;

	root = handle_pipes(&tokens);
	if (!root)
	{
		app->exit_status = ES_ERROR;
		return (NULL);
	}
	return (root);
}

static t_ast_node	*handle_pipes(t_token **tokens)
{
	t_ast_node	*left;
	t_ast_node	*right;

	left = ast_command(tokens);
	if (!left)
		return (NULL);
	while (*tokens && (*tokens)->type == TOKEN_PIPE)
	{
		*tokens = (*tokens)->next;
		right = ast_command(tokens);
		if (!right)
			return (NULL);
		left = ast_node_insert(left, NODE_PIPE, NULL);
		if (!left)
			return (NULL);
		left->right = right;
	}
	return (left);
}

static t_ast_node	*ast_command(t_token **tokens)
{
	t_token		*redir_tokens[256];
	int			redir_count = 0;
	char		*data_tmp[1024];
	int			data_count = 0;
	char		**data;
	t_ast_node	*cmd;

	// Collect all tokens (redirections and words) until pipe or end
	while (*tokens && (*tokens)->type != TOKEN_PIPE)
	{
		if ((*tokens)->type == TOKEN_REDIRECTION_IN ||
			(*tokens)->type == TOKEN_REDIRECTION_OUT ||
			(*tokens)->type == TOKEN_APPEND ||
			(*tokens)->type == TOKEN_HEREDOC)
		{
			if (!(*tokens)->next || (*tokens)->next->type != TOKEN_WORD)
			{
				ft_printf("Syntax error: missing file after redirection\n");
				return (NULL);
			}
			redir_tokens[redir_count++] = *tokens;
			redir_tokens[redir_count++] = (*tokens)->next;
			*tokens = (*tokens)->next->next;
		}
		else if ((*tokens)->type == TOKEN_WORD)
		{
			data_tmp[data_count++] = ft_strdup((*tokens)->data);
			*tokens = (*tokens)->next;
		}
		else
			break ;
	}
	// Allocate and fill command data
	data = malloc(sizeof(char *) * (data_count + 1));
	if (!data)
		return (NULL);
	ft_memcpy(data, data_tmp, sizeof(char *) * data_count);
	data[data_count] = NULL;
	cmd = ast_new_node(NODE_CMD, data);
	if (!cmd)
		return (free(data), NULL);
	// Attach redirections in reverse order
	for (int j = redir_count - 2; j >= 0; j -= 2)
	{
		t_node_types	type = redirection_type(redir_tokens[j]);
		char			**redir_data;

		redir_data = malloc(sizeof(char *) * 2);
		if (!redir_data)
			return (free_ast(cmd), NULL);
		redir_data[0] = ft_strdup(redir_tokens[j + 1]->data);
		redir_data[1] = NULL;
		t_ast_node	*redir_node = ast_new_node(type, redir_data);
		if (!redir_node)
		{
			free(redir_data[0]);
			free(redir_data);
			return (free_ast(cmd), NULL);
		}
		redir_node->right = cmd;
		cmd = redir_node;
	}
	return (cmd);
}
