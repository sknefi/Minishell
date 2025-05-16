#ifndef BUILTIN_H
# define BUILTIN_H

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
 * @return 0 on success, -1 on failure (malloc failed), 
 * -2 on failure (command not found)
*/
int			exec_builtin(t_app *app, char **cmd_args);

/**
 * @brief echobuiltin
 * @param app The application
 * @param cmd_args The command arguments
 * @return 0 on success, -1 on failure (malloc failed)
 * @example echo "Hello, World!"
 * @example echo $USER > file.txt
 * @example echo $USER $HOME $SHELL
*/
int			sh_echo(t_app *app, char **cmd_args);

/**
 * @brief pwd builtin
 * @param app The application
 * @param cmd_args The command arguments
 * @return 0 on success, -1 on failure (malloc failed)
 * @example pwd
*/
int			sh_pwd(t_app *app, char **cmd_args);

/**
 * @brief cd builtin
 * @param app The application
 * @param cmd_args The command arguments
 * @return 0 on success, -1 on failure (malloc failed), 
 * 1 on failure (directory not found)
 * @example cd ..
 * @example cd /
 * @example cd ~
 * @example cd -
 * @example cd
*/
int			sh_cd(t_app *app, char **cmd_args);

/**
 * @brief export builtin
 * @param app The application
 * @param cmd_args The command arguments
 * @return 0 on success, -1 on failure (malloc failed)
 * @example export VAR=VALUE
 * @example export VAR=VALUE1 VALUE2
 * @example export VAR1=VALUE1 VAR2=VALUE2
 * @example export
*/
int			sh_export(t_app *app, char **cmd_args);

/**
 * @brief unset builtin
 * @param app The application
 * @param cmd_args The command arguments
 * @return 0 on success
 * @example unset VAR
 * @example unset VAR1 VAR2
 */
int			sh_unset(t_app *app, char **cmd_args);

/**
 * @brief env builtin
 * @param app The application
 * @param cmd_args The command arguments
 * @return 0 on success
 * @example env
 */
int			sh_env(t_app *app, char **cmd_args);

/**
 * @brief exit builtin
 * @param app The application
 * @param cmd_args The command arguments
 * @return 0 on success
 * @example exit
 */
int			sh_exit(t_app *app, char **cmd_args);

/**
 * @brief Replaces an environment variable
 * @param app The application
 * @param key The key
 * @return 0 on success, -1 on failure (malloc failed)
 */
int			handle_replace_export(t_app *app, char *key);

/**
 * @brief Appends an environment variable
 * @param app The application
 * @param key The key
 * @return 0 on success, -1 on failure (malloc failed)
 */
int			handle_append_export(t_app *app, char *key);

/**
 * @brief Gets the value of an environment variable
 * @param name The name of the environment variable (USER, HOME, ...)
 * @param env The environment variables
 * @return The value of the environment variable (NULL if not found)
*/
char		*get_env_var(const char *name, char **env);

/**
 * @brief Sorts an array of environment variables
 * @param env The array of environment variables
*/
char		**show_env_sort(char **env);

/**
 * @brief Prints an array of environment variables
 * @param env The array of environment variables
*/
void		show_env(char **env);

/**
 * @brief Gets the length of the key of an environment variable
 * @param str The environment variable
 * @return The length of the key of the environment variable
*/
size_t		get_env_key_len(char *str);

/**
 * @brief Gets the key of an environment variable
 * @param str The environment variable
 * @return The key of the environment variable
*/
char		*get_env_key(char *str, char **env);

#endif
