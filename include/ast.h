#ifndef AST_H
# define AST_H

# include "minishell.h"
# include "structs.h"

t_ast_node	*parse(t_token *tokens);
t_ast_node	*ast_new_node(t_node_types type, char **data);
t_ast_node	*ast_node_insert(t_ast_node *root, t_node_types type, char **data);
void		free_ast(t_ast_node *node);

#endif
