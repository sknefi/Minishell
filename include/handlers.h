#ifndef HANDLERS_H
# define HANDLERS_H

# include "minishell.h"

int	handle_redirection_out(t_app *app, t_ast_node *node, int type);
int	handle_redirection_in(t_app *app, t_ast_node *node);

#endif
