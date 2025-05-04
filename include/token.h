#ifndef TOKEN_H
# define TOKEN_H

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

#endif