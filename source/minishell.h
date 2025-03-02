#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

#include "token/token.h"

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
	TOEKN_PIPE,
	TOKEN_FILE
}	t_token_type;


void	lexer(void);


#endif
