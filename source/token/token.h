#ifndef TOKEN_H
# define TOKEN_H

#include "../structs.h"

t_token	*token_append(t_token *head, char *data, int type);
void	free_tokens(t_token *token);
char	*get_env_var(char *token);

#endif
