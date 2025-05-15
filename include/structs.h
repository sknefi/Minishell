#ifndef STRUCTS_H
# define STRUCTS_H

/**
 * @brief Forward declaration of `struct s_app`
 * This tells the compiler that `struct s_app` exists, 
 * allowing `t_builtin` to use it.
 */
typedef struct s_app	t_app;

/**
 * @brief Struct of the token
 * date: the data of the token
 * type: the type of the token
 * next: pointer to the next token
 * prev: pointer to the previous token
*/
typedef struct s_token
{
	int				type;
	char			*data;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_input
{
	char	*line;
	int		i;
	int		token_error;
}	t_input;

/**
 * @brief Struct of builtins
 * name: name of the builtin
 * f: function pointer to the builtin, taking a pointer 
 * to t_app and an argument vector
*/
typedef struct s_builtin
{
	char	*name;
	int		(*f)(t_app *app, char **cmd_args); // main change
}	t_builtin;

/**
 * @brief Token types
 * TOKEN_COMMAND: command token
 * 				[ls, echo, ...]
 * TOKEN_ARG`: argument token
 * 				[-n, -l, -la, ...]
 * TOKEN_PIPE: pipe token
 * 				[|]
 * TOKEN_WORD_VAR: word token to be replaced with variable
 * 				[$HOME, $USER, ...]
 * 				+examples 	~>$HOME 
 * 							~>"$HOME"
 * TOKEN_WORD_NVAR: word token without variable
 * 				[Hi, How is ur day, ...], but also
 * 				[Hello $USER, $HOME, ...] 
 * 				+examples 	~> Hi
 * 							~> How is ur day
 * 							~> "How is ur day"
 * 							~> 'How is ur day'
 * 							~> '"Hello $USER"'
 * TOKEN_REDIRECTION: redirection token
 * 				[>, <, <<]
 * 
 * TOKEN_HERE_DOC: here document token
 * 				[<<EOF]]
 * 
 * TOKEN_FILE: file token
 * 				[file.txt, file2.txt, ...]
 * 
 * Difference between TOKEN_WORD_VAR and TOKEN_WORD_NVAR:
 * 		TOKEN_WORD_VAR is a word token that is a variable
 * 		TOKEN_WORD_NVAR is a word token that does not contain a variable, 
 * 			even if it has $ in it -> the whole token is just a text
*/
typedef enum e_token_types
{
	TOKEN_WORD,
	TOKEN_COMMAND,
	TOKEN_PIPE,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_REDIRECTION_IN,
	TOKEN_REDIRECTION_OUT,
	TOKEN_SINGLE_QUOTES,
	TOKEN_DOUBLE_QUOTES,
}	t_token_types;

typedef enum e_node_types
{
	NODE_CMD,
	NODE_PIPE,
	NODE_REDIRECTION_IN,
	NODE_REDIRECTION_OUT,
	NODE_APPEND,
	NODE_HEREDOC,
	ERROR,
}	t_node_types;

typedef struct s_ast_node
{
	t_node_types		type;
	char				**data;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

/**
 * @brief Struct of the app, stores every information about the app
 * exit_status: exit status of the last command
 * env: environment variables
 * builtins: builtins, we were supposed to implement
 * token: linked list of tokens
 * root: root of the AST
*/
typedef struct s_app
{
	int			exit_status;
	char		**env;
	t_builtin	**builtins;
	t_token		*token;
	t_ast_node	*root;
}				t_app;

#endif
