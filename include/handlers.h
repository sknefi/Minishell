#ifndef HANDLERS_H
# define HANDLERS_H

# include "minishell.h"

/**
 * @brief Handle redirection out (>, >>), even for multiple files (a > b > c)
 * @param app The application
 * @param node The node to handle
 * @param type The type of redirection
 * @return 0 on success, 1 on failure
 */
int	handle_redirection_out(t_app *app, t_ast_node *node);

/**
 * @brief Handle redirection in (<)
 * @param app The application
 * @param node The node to handle
 * @return 0 on success, 1 on failure
 */
int	handle_redirection_in(t_app *app, t_ast_node *node);

/**
 * @brief Create files and redirect stdout to the top file
 * @param node The node to create files for
 * @param saved_stdout The saved stdout file descriptor
 * @return 0 on success, 1 on failure
 * 
 * @example echo HELL > a > b > c
 * 
 * Our AST is:
 * c (top) -> b -> a -> echo HELL
 * 
 * We want to create a, b but only write to c
 * 
 */
int	create_files(t_ast_node *node, int saved_stdout);

/**
 * @brief Find the command node, which is the rightmost node in the AST
 * 
 * this is used to execute the command after creating the files in redirection
 * @param node The node to find the command node in
 * @return The command node
 */
t_ast_node	*find_command_node(t_ast_node *node);

/**
 * @brief Handle pipe
 * @param app The application
 * @param node The node to handle
 */
int	handle_pipe(t_app *app, t_ast_node *node);

#endif
