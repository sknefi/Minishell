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

/**
 * @brief Struct of builtins
 * name: name of the builtin
 * f: function pointer to the builtin, taking a pointer 
 * to t_app and an argument vector
*/
typedef struct s_builtin
{
	char	*name;
	int		(*f)(t_app *app, t_token *token);
}	t_builtin;

/**
 * @brief Struct of the app, stores every information about the app
*/
typedef struct s_app
{
	int			exit_status;
	char		**env;
	t_builtin	**builtins;
}				t_app;

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
typedef enum e_token_type
{
	TOKEN_COMMAND,
	TOKEN_ARG,
	TOKEN_PIPE,
	TOKEN_WORD_VAR,
	TOKEN_WORD_NVAR,
	TOKEN_REDIRECTION,
	TOKEN_HERE_DOC,
	TOKEN_FILE
}	t_token_type;

#endif
