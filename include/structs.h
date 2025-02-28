#ifndef STRUCTS_H
# define STRUCTS_H

/**
 * @brief Forward declaration of `struct s_app`
 * This tells the compiler that `struct s_app` exists, 
 * allowing `t_builtin` to use it.
 */
typedef struct s_app	t_app;

/**
 * @brief Struct of builtins
 * name: name of the builtin
 * f: function pointer to the builtin, taking a pointer 
 * to t_app and an argument vector
*/
typedef struct s_builtin
{
	char	*name;
	int		(*f)(t_app *app, char **av);
}	t_builtin;

/**
 * @brief Struct of the app, stores every information about the app
*/
typedef struct s_app
{
	int			exit_status;
	char		**env;
	t_builtin	**builtins;
}				t_app;

#endif
