#include "../../include/minishell.h"

// create pipe
// fork left
// in left child: redirect stdout to pipe write-end, close read-end, exec_ast(left)
// fork right
// in right child: redirect stdin to pipe read-end, close write-end, exec_ast(right)
// in parent: wait for both
int	handle_pipe(t_app *app, t_ast_node *node)
{
	
}