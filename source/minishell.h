#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <signal.h>

#include "../libft/libft.h"
#include "structs.h"
//#include "token/token.h"
#include "ast/ast.h"

int	prompt(t_token **token, t_ast_node **node);
void	sig_handler();

t_token	*token_append(t_token *head, char *data, int type);
void	free_tokens(t_token *token);
char	*get_env_var(char *token);
int	ft_isspace(char	c);
int	ft_strcmp(const char *s1, const char *s2);
int	is_command(char *str);

char	*handle_quotes(char *line, int *i);
char	*handle_operators(char *line, int *i);
char	*handle_word(char *line, int *i);
char *ft_strjoin_free(char *s1, char *s2);

#endif
