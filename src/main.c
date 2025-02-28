#include "../include/minishell.h"

char	*get_val_of_var(const char *s)
{
	int		i;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	if (s[i] == '=' && s[i + 1])
		return ((char *)s + i + 1);
	return (NULL);
}

char	*get_env_var(const char *name, char **env)
{
	int		i;
	size_t	len;

	if (!name || !env)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
			return (get_val_of_var(env[i]));
		i++;
	}
	return (NULL);
}

int		main(int argc, char **argv, char **env)
{
	t_app		*app;
	(void)argc;
	(void)argv;

	app = init_app(env);
	if (!app)
		return (EXIT_FAILURE);
	
	exec_builtin("env", env, app);
	
	
	// p("builtins[4]->name: %s\n", builtins[4]->name);
	// p("PATH: %s\n", get_env_var("PATH", env));
	clean_app(app);
	return 0;
}
