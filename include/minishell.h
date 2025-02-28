#ifndef MINISHEL_H
# define MINISHEL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include <sysexits.h>

# include "../libft_divinus/libft.h"
# include "structs.h"
# include "builtin.h"

# define Y		"\033[1;33m"
# define G		"\033[1;32m"
# define C 		"\033[1;36m"
# define RED		"\033[1;31m"
# define RST 		"\033[0m"

# define p(...)	ft_printf(__VA_ARGS__)

/**
 * @brief Initialize the app struct
*/
t_app	*init_app(char **env);

/**
 * @brief Frees the app struct
*/
void	clean_app(t_app *app);

#endif
