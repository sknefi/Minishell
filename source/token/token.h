#ifndef TOKEN_H
# define TOKEN_H

#include "../structs.h"

t_token	*token_append(t_token *head, char *data, int type);
void	free_tokens(t_token *token);
char	*get_env_var(char *token);
int	ft_isspace(char	c);
int	ft_strcmp(const char *s1, const char *s2);

#endif
