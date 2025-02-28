#ifndef MINISHELL_H
# define MINISHELL_H

#include <regex>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_token
{
	char	*token;
	int		type;
	s_token	*next;
	s_token	*prev;
}	t_token;

typedef enum e_token_type
{
}	t_token_type;
void	lexer(void);


#endif
