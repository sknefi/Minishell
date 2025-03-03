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
	TOKEN_WORD,
	TOKEN_HEREDOC,
	TOKEN_APPEND,
	TOKEN_REDIRECTION_IN,
	TOKEN_REDIRECTION_OUT,
	TOKEN_PIPE
}	t_token_type;

#endif
