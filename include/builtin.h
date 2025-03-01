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
 * @param name The name of the environment variable
 * @param env The environment variables
 * @return The value of the environment variable (NULL if not found)
*/
char	*get_env_var(const char *name, char **env);


#endif
