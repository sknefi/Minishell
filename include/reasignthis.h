#ifndef REASIGNTHIS_H
#define REASIGNTHIS_H

#include "minishell.h"

// TYM_COMMENT - put them in some header file, I believe u know where to put them better than me
char	*handle_operators(char *line, int *i);
char	*handle_word(char *line, int *i);
void	remove_quotes(char *str);

#endif
