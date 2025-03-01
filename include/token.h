#ifndef TOKEN_H
# define TOKEN_H

# include "structs.h"

/**
 * @brief Initialize a new token
 * @param type The type of the token from enum
 * @param data The data of the token (string)
*/
t_token	*token_init(int type, char *data);

/**
 * @brief Append a token to the end of the list
 * @param head The head of the list
 * @param data The data of the token (string)
 * @param type The type of the token from enum
*/
t_token	*token_append(t_token *head, char *data, int type);

/**
 * @brief Cleans whole token list
 * @param token The head of the list
*/
void	token_clean(t_token *head);


void	token_print(t_token *token);

void	token_print_inline(t_token *token);

#endif