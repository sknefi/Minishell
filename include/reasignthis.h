#ifndef REASIGNTHIS_H
#define REASIGNTHIS_H

#include "minishell.h"

char	*handle_operators(char *line, int *i);
char	*ft_strjoin_free(char *s1, char *s2);
void    *ft_realloc_token(void *ptr, size_t size);
char	*handle_word(char *line, int *i);
t_token	*token_append(t_token *head, char *data, int type);
void	free_tokens(t_token *token);
int		ft_isspace(char	c);
int		ft_strcmp(const char *s1, const char *s2);
void	remove_quotes(char *str);
int		prompt(t_token **token, t_ast_node **node);

#endif
