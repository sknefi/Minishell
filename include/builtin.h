#ifndef BUILTINT_H
# define BUILTINT_H

# include "structs.h"
# include "minishell.h"

/**
 * @brief Initialize builtins, each builtin has a name and a function pointer
 * name is on the stack => no need to free it, can't be modified
 * @return Struct of builtins
*/
t_builtin	**init_builtins(void);

/**
 * @brief Frees each builtin and the array of builtins
*/
void		free_builtins(t_builtin **builtins);

/**
 * @brief Execute a builtin by its name
 * @param app The application
 * @param token The token
 * @return 0 on success, -1 on failure (malloc failed), 1 on failure (command not found)
*/
int			exec_builtin(t_app *app, char **cmd_args);

int			sh_echo(t_app *app, char **cmd_args);
int			sh_pwd(t_app *app, char **cmd_args);
int			sh_cd(t_app *app, char **cmd_args);
int			sh_export(t_app *app, char **cmd_args);
int			sh_unset(t_app *app, char **cmd_args);
int			sh_env(t_app *app, char **cmd_args);
int			sh_exit(t_app *app, char **cmd_args);

int			handle_replace_export(t_app *app, char *key);
int			handle_append_export(t_app *app, char *key);

/**
 * @brief Gets the value of an environment variable
 * @param name The name of the environment variable (USER, HOME, ...)
 * @param env The environment variables
 * @return The value of the environment variable (NULL if not found)
*/
char	*get_env_var(const char *name, char **env);

/**
 * @brief Sorts an array of environment variables
 * @param env The array of environment variables
*/
char	**show_env_sort(char **env);

/**
 * @brief Prints an array of environment variables
 * @param env The array of environment variables
*/
void	show_env(char **env);

/**
 * @brief Gets the length of the key of an environment variable
 * @param str The environment variable
 * @return The length of the key of the environment variable
*/
size_t	get_env_key_len(char *str);

/**
 * @brief Gets the key of an environment variable
 * @param str The environment variable
 * @return The key of the environment variable
*/
char	*get_env_key(char *str, char **env);

/**
 * @brief Unsets an environment variable
 * @param app The application
 * @param token The token
 * @return 0 if key is not found, 0 if key is unset
*/
// int	sh_unset(t_app *app);

#endif
