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
void	free_builtins(t_builtin **builtins);

/**
 * @brief Execute a builtin by its name
*/
int	exec_builtin(char *name, char **av, t_app *app);


int		sh_echo(t_app *app, char **av);
int		sh_pwd(t_app *app, char **av);
int		sh_cd(t_app *app, char **av);
int		sh_export(t_app *app, char **av);
int		sh_unset(t_app *app, char **av);
int		sh_env(t_app *app, char **av);
int		sh_exit(t_app *app, char **av);

#endif
