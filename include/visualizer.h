#ifndef VISUALIZER_H
# define VISUALIZER_H

# include "minishell.h"

// TYM_COMMENT
void	print_prefix(int depth, int is_left);
const char *node_type_to_str(t_node_types type);
void	print_cmd_data(char **data);
void	print_ast(const t_ast_node *node, int depth, int is_left);

#endif
