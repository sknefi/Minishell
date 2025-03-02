#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_token
{
	int				type;
	char			*data;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef enum e_token_type
{
	TOKEN_COMMAND,
	TOKEN_ARG,
	TOKEN_WORD_VAR,
	TOKEN_WORD_NVAR,
	TOKEN_REDIRECTION,
	TOKEN_PIPE,
	TOKEN_FILE
}	t_token_type;

#endif
