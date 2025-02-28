#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_token
{
	char	*token;
	int		type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef enum e_token_type
{
	TOKEN_WORD
}	t_token_type;
void	lexer(void);


#endif
