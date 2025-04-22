#include "../minishell.h"

static t_ast_node	*handle_pipes(t_token **token);
static t_ast_node	*ast_command(t_token **tokens);
static t_ast_node	*parse_redirection(t_token **tokens, t_ast_node *cmd);

t_ast_node	*parse(t_token *tokens)
{
	return (handle_pipes(&tokens));
}

static t_ast_node	*handle_pipes(t_token  **tokens)
{
	t_ast_node	*left;
	t_ast_node	*right;

	left = ast_command(tokens);
	while (*tokens && (*tokens)->type == TOKEN_PIPE)
	{
		*tokens = (*tokens)->next;
		right = ast_command(tokens);
		left = ast_node_insert(left, NODE_PIPE, NULL);
		left->right = right;
	}
	return (left);
}

static t_ast_node	*ast_command(t_token **tokens)
{
	char	**data;
	int		i;
	int		j;
	t_token *tmp;
	t_ast_node	*cmd;

	i = 0;
	j = 0;
	tmp = *tokens;
	while (tmp && (tmp->type == TOKEN_WORD || tmp->type == TOKEN_SINGLE_QUOTES || tmp->type == TOKEN_DOUBLE_QUOTES)) //TODO
	{
		i++;
		tmp = tmp->next;
	}
	data = malloc(sizeof(char *) * (i + 1));
	if (!data)
		return (NULL);
	while (*tokens && ((*tokens)->type == TOKEN_WORD || (*tokens)->type == TOKEN_SINGLE_QUOTES || (*tokens)->type == TOKEN_DOUBLE_QUOTES)) //TODO
	{
		data[j++] = (*tokens)->data;
		*tokens = (*tokens)->next;
	}
	data[j] = NULL;
	cmd = ast_new_node(NODE_CMD, data);
	while (*tokens && ((*tokens)->type == TOKEN_REDIRECTION_IN || (*tokens)->type == TOKEN_REDIRECTION_OUT || (*tokens)->type == TOKEN_APPEND || (*tokens)->type == TOKEN_HEREDOC))
		cmd = parse_redirection(tokens, cmd);
	return (cmd);
}

static t_ast_node	*parse_redirection(t_token **tokens, t_ast_node *cmd)
{
	t_token *redir;
	t_ast_node *redir_node;
	char	**data;

	redir = *tokens;
	*tokens = (*tokens)->next;
	if (!*tokens || (*tokens)->type != TOKEN_WORD)
	{
		ft_printf("Error\n");
		return (NULL);
	}
	if (redir->type == TOKEN_REDIRECTION_IN)
		redir_node = ast_new_node(NODE_REDIRECTION_IN, NULL);
	else if (redir->type == TOKEN_REDIRECTION_OUT)
		redir_node = ast_new_node(NODE_REDIRECTION_OUT, NULL);
	else if (redir->type == TOKEN_APPEND)
		redir_node = ast_new_node(NODE_APPEND, NULL);
	else if (redir->type == TOKEN_HEREDOC)
		redir_node = ast_new_node(NODE_HEREDOC, NULL);
	else
	{
		ft_printf("Error\n");
		return (NULL);
	}
	redir_node->right = cmd;
	data = malloc(2 * sizeof(char *));
	data[0] = (*tokens)->data;
	data[1] = NULL;
	redir_node->data = data;
	redir_node->right = cmd;
	*tokens = (*tokens)->next;
	return (redir_node);
}
