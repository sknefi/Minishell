#ifndef REASIGNTHIS_H
#define REASIGNTHIS_H

#include "minishell.h"

// TYM_COMMENT - put them in some header file, I believe u know where to put them better than me
char	*handle_operators(t_input *input, t_app *app);
char	*handle_word(t_input *input, t_app *app);
void	remove_quotes(char *str);

#endif
