#include "../../include/minishell.h"

#define PREFIX_ENV "declare -x "

char	**env_sort(char **env)
{
	int		i;
	int		j;
	char	*temp;
	char	**new_env;
	
	i = 0;
	new_env = init_env(env);
	if (!new_env)
		return (NULL);
	while (new_env[i])
	{
		j = i + 1;
		while (new_env[j])
		{
			if (ft_strcmp(new_env[i], new_env[j]) > 0)
			{
				temp = new_env[i];
				new_env[i] = new_env[j];
				new_env[j] = temp;
			}
			j++;
		}
		i++;
	}
	return (new_env);
}

void	show_env(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		ft_printf("%s\n", env[i]);
		i++;
	}
}

void	show_env_prefix(char **env)
{
	int		i;
	int		j;
	int		first_es;

	i = 0;
	while (env[i])
	{
		ft_printf("%s", PREFIX_ENV);
		j = 0;
		first_es = 0;
		while (env[i][j])
		{
			write(STDOUT_FILENO, &env[i][j], 1);
			if (env[i][j] == '=' && !first_es)
			{
				first_es = 1;
				write(STDOUT_FILENO, "\"", 1);
			}
			j++;
		}
		write(STDOUT_FILENO, "\"\n", 2);
		i++;
	}
}

int	sh_env(t_app *app, char **cmd_args)
{
	(void)cmd_args;
	if (cmd_args[1])
	{
		ft_printf(RED "env: %s: No such file or directory\n" RST, cmd_args[1]);
		return (1);
	}
	show_env(app->env);
	return (0);
}
