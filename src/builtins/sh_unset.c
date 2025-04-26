#include "../../include/minishell.h"

int	sh_unset(t_app *app, char **cmd_args)
{
	int		i;
	char	*key;
	size_t	key_len;

	p(Y"cmd_args: %s\n" RST, cmd_args[0]);
	key = cmd_args[1];
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
			break ;
		}
		i++;
	}
	show_env(app->env);
	return (0);
}
