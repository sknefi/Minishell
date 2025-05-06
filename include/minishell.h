#ifndef MINISHEL_H
# define MINISHEL_H

// sh -> shell
// ast -> abstract syntax tree
// env -> environment

// LIBRARIES
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include <sysexits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <limits.h>

// INCLUDES
# include "../libft_divinus/libft.h"
# include "structs.h"
# include "builtin.h"
# include "token.h"
# include "utils.h"
# include "ast.h"
# include "visualizer.h"
# include "handlers.h"
# include "reasignthis.h"
# include "signals.h"
# include "env.h"

// COLORS
# define Y		"\033[1;33m"
# define G		"\033[1;32m"
# define C 		"\033[1;36m"
# define RED	"\033[1;31m"
# define RST 	"\033[0m"

// EXIT STATUS
# define NOT_BUILTIN		 -2 // command is not a builtin, exec external command
# define ES_FAILED	 		 -1
# define ES_OK				  0
# define ES_ERROR			  1
# define ES_CMD_NOT_FOUND	127

/**
 * @brief Initialize the app struct
*/
t_app	*init_app(char **env);

/**
 * @brief Frees the app struct
*/
void	clean_app(t_app *app);

/**
 * @brief Executes a command (builtin or external)
 * @param app The application
 * @param token The token
 * @return 0 on success, 1 on failure (command not found), -1 on failure (malloc failed)
*/
int	sh_exec(t_app *app);

/**
 * @brief Executes an external command
 * @param app The application
 * @param cmd_args The command arguments
 * @return 0 on success, 1 on failure (command not found), -1 on failure (malloc failed)
*/
int	exec_external(t_app *app, char **cmd_args);

/**
 * @brief Executes an AST node
 * @param node The AST node
 * @param app The application
 * @return 0 on success, 1 on failure (command not found), -1 on failure (malloc failed)
*/
int	exec_ast_node(t_ast_node *node, t_app *app);

// TYM_COMMENT
int		prompt(t_token **token, t_ast_node **node);

#endif
