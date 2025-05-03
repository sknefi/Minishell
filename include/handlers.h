#ifndef HANDLERS_H
# define HANDLERS_H

# include "minishell.h"

int	handle_redirection_out(t_app *app, t_ast_node *node, int type);
int	handle_redirection_in(t_app *app, t_ast_node *node);
int	create_files(t_ast_node *node, int saved_stdout);
t_ast_node	*find_command_node(t_ast_node *node);
int redirect_stdout(t_ast_node *node, int saved_stdout);

#endif
