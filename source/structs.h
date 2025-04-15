#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum e_token_types
{
	TOKEN_WORD,
	TOKEN_COMMAND,
	TOKEN_PIPE,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_REDIRECTION_IN,
	TOKEN_REDIRECTION_OUT,
}	t_token_types;

typedef enum e_node_types
{
	NODE_CMD,
	NODE_PIPE,
	NODE_REDIRECTION_IN,
	NODE_REDIRECTION_OUT,
	NODE_APPEND,
	NODE_HEREDOC,
}	t_node_types;

typedef struct s_token
{
	int				type;
	char			*data;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_ast_node
{
	t_node_types				type;
	char				**data;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

#endif
