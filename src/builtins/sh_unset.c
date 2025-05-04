#include "../../include/minishell.h"

/**
 * @brief Unset a single environment variable
 * @param app The application
 * @param key The key to unset
 * @return 0 on success
 */
static int	unset_single_var(t_app *app, char *key)
{
	int		i;
	size_t	key_len;

	if (!key)
		return (0);
	key_len = get_env_key_len(key);
	i = 0;
	while (app->env[i])
	{
		if (ft_strncmp(app->env[i], key, key_len) == 0 &&
			(app->env[i][key_len] == '=' || app->env[i][key_len] == '\0'))
		{
			free(app->env[i]);
			while (app->env[i + 1])
			{
				app->env[i] = app->env[i + 1];
				i++;
			}
			app->env[i] = NULL;
			break;
		}
		i++;
	}
	return (0);
}

int	sh_unset(t_app *app, char **cmd_args)
{
	int	key_index;
	
	key_index = 1;
	while (cmd_args[key_index])
	{
		unset_single_var(app, cmd_args[key_index]);
		key_index++;
	}
	return (0);
}
