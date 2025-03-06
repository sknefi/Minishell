#ifndef BUILTINT_H
# define BUILTINT_H

# include "structs.h"

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
*/
int			exec_builtin(char *name, t_token *token, t_app *app);

int			sh_echo(t_app *app, t_token *token);
int			sh_pwd(t_app *app, t_token *token);
int			sh_cd(t_app *app, t_token *token);
int			sh_export(t_app *app, t_token *token);
int			sh_unset(t_app *app, t_token *token);
int			sh_env(t_app *app, t_token *token);
int			sh_exit(t_app *app, t_token *token);

/**
 * @brief Gets the value of an environment variable
 * @param name The name of the environment variable (USER, HOME, ...)
 * @param env The environment variables
 * @return The value of the environment variable (NULL if not found)
*/
char	*get_env_var(const char *name, char **env);

/**
 * @brief Counts the number of pointers in an array of pointers
 * @param str The array of pointers
 * @return The number of pointers in the array
*/
size_t	count_pointer(char **str);

/**
 * @brief Frees an array of pointers, from the last pointer to the first
 * @param str The array of pointers
 * @param i The number of pointers to free
*/
void	free_dpp(char **str, int i);

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
int	sh_unset(t_app *app, t_token *token);

#endif
