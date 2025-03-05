#include "../../include/minishell.h"

char	**sh_env_sort(char **env)
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
		p("%s\n", env[i]);
		i++;
	}
}

int	sh_env(t_app *app, t_token *token)
{
	(void)token;
	show_env(app->env);
	app->exit_status = 0;
	return (0);
}
