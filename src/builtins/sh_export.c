#include "../../include/minishell.h"

static char	**append_env(char **from, char **to, char *new_var, t_app *app)
{
	int	i;

	i = 0;
	while (from[i])
	{
		to[i] = ft_strdup(from[i]);
		if (!to[i])
			return (free_dpp_i(from, i), NULL);
		free(from[i]);
		i++;
	}
	to[i] = ft_strdup(new_var);
	if (!to[i])
		return (free_dpp_i(to, i), NULL);
	to[i + 1] = NULL;
	free(from);
	app->env = to;
	return (to);
}

static int	handle_only_export(t_app *app)
{
	char	**new_env;

	new_env = env_sort(app->env);
	if (!new_env)
		return (-1);
	show_env_prefix(new_env);
	free_env(new_env);
	return (0);
}

int	handle_append_export(t_app *app, char *key)
{
	char	**new_env;
	size_t	env_size;

	if (!contains_equal_sign(key))
		return (0); // idk why, bash behavior
	env_size = count_pointer(app->env);
	new_env = malloc(sizeof(char *) * (env_size + 2)); // +2 for new var and NULL terminator
	if (!new_env)
		return (-1);
	if (!append_env(app->env, new_env, key, app))
		return (-1);
	return (0);
}

int	handle_replace_export(t_app *app, char *key)
{
	int	i;

	if (!contains_equal_sign(key))
		return (0); // idk why, bash behavior
	i = 0;
	while (app->env[i])
	{
		if (ft_strncmp(app->env[i], key, get_env_key_len(key)) == 0)
		{
			free(app->env[i]);
			app->env[i] = ft_strdup(key);
			if (!app->env[i])
				return (-1);
			break ;
		}
		i++;
	}
	return (0);
}

int	sh_export(t_app *app, char **cmd_args)
{
	int		i;
	char	*key;
	
	if (!cmd_args[1])
		return (handle_only_export(app));
	i = 1;
	while (cmd_args[i])
	{
		key = get_env_key(cmd_args[i], app->env);
		if (!key)
		{
			if (handle_append_export(app, cmd_args[i]) == -1)
				return (ES_FAILED);
		}
		else
		{
			if (handle_replace_export(app, cmd_args[i]) == -1)
				return (ES_FAILED);
		}
		i++;
	}
	return (ES_OK);
}
