#ifndef MINISHEL_H
# define MINISHEL_H

// sh -> shell

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

# include "../libft_divinus/libft.h"
# include "structs.h"
# include "builtin.h"
# include "token.h"
# include "utils.h"
# include "ast.h"
# include "visualizer.h"
# define Y		"\033[1;33m"
# define G		"\033[1;32m"
# define C 		"\033[1;36m"
# define RED	"\033[1;31m"
# define RST 	"\033[0m"

// # define ft_printf(...)	ft_printf(__VA_ARGS__)

/**
 * @brief Initializes the environment variables
 * @param env The environment variables
 * @return The initialized environment variables on heap
*/
char	**init_env(char **env);

/**
 * @brief Frees the environment variables
 * @param env The environment variables
 */
void	free_env(char **env);


/**
 * @brief Initialize the app struct
*/
t_app	*init_app(char **env);

/**
 * @brief Frees the app struct
*/
void	clean_app(t_app *app);

/**
 * @brief Executes an external command
 * @param app The application
 * @param token The token
 * @return 0 on success, 1 if command not found, -1 on error
*/
// int	exec_external(t_app *app, t_token *token);

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

int	prompt(t_token **token, t_app *app);
void	sig_handler();

t_token	*token_append(t_token *head, char *data, int type);
void	free_tokens(t_token *token);
int	ft_isspace(char	c);
int	ft_strcmp(const char *s1, const char *s2);
int	is_command(char *str);


#endif
