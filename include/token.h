#ifndef TOKEN_H
# define TOKEN_H

#include <stdio.h>
# include "structs.h"
/**
 * @brief Append a token to the end of the list
 * @param head The head of the list
 * @param data The data of the token (string)
 * @param type The type of the token from enum
*/
t_token	*token_append(t_token *head, char *data, int type);



// TYM_COMMENT
void	free_tokens(t_token *token);
t_token	*token_append(t_token *head, char *data, int type);
void	free_tokens(t_token *token);
int	grow_token(t_app *app, char **token, size_t *size, char c);
int	expand_exit_status(t_input *input, char **token, \
		size_t *size, t_app *app);
int	expand_env(t_input *input, char **token, size_t *size, t_app *app);

#endif
