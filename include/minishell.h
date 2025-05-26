/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkarika <fkarika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:08:05 by fkarika           #+#    #+#             */
/*   Updated: 2025/05/26 15:20:07 by fkarika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// sh -> shell
// ast -> abstract syntax tree
// env -> environment
//static volatile int    g_heredoc_interrupted; ERASE_IT
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
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>

// INCLUDES
# include "../libft/libft.h"
# include "structs.h"
# include "builtin.h"
# include "token.h"
# include "utils.h"
# include "ast.h"
# include "handlers.h"
# include "signals.h"
# include "env.h"

// COLORS
# define Y		"\033[1;33m"
# define G		"\033[1;32m"
# define C 		"\033[1;36m"
# define RED	"\033[1;31m"
# define RST 	"\033[0m"

// EXIT STATUS
# define CHILD_NO_STATUS	 -3
# define NOT_BUILTIN 		 -2
# define ES_FAILED	 		 -1
# define ES_OK				  0
# define ES_ERROR			  1
# define ES_CMD_NOT_FOUND	127
# define ES_EXIT			130
# define ES_SIGQUIT			131

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
 * @return 0 on success, 1 on failure (command not found), 
 * -1 on failure (malloc failed) or anything that exec_external returns
*/
int		sh_exec(t_app *app);

/**
 * @brief Executes an external command
 * @param app The application
 * @param cmd_args The command arguments
 * @return 0 on success, 1 on failure (command not found), 
 * -1 on failure (malloc failed) or anything that exec_external returns
*/
int		exec_external(t_app *app, char **cmd_args);

/**
 * @brief Executes an AST node
 * @param node The AST node
 * @param app The application
 * @return 0 on success, 1 on failure (command not found), 
 * -1 on failure (malloc failed) or anything that exec_external returns
*/
int		exec_ast_node(t_ast_node *node, t_app *app);

int		get_child_exit_status(int status);

void	print_banner(void);

#endif
