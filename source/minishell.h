#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <signal.h>

#include "structs.h"
#include "token/token.h"

void	lexer(t_token **token);
void	sig_handler();


#endif
