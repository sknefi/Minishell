#include "../../include/minishell.h"

/**
 * @brief Allocates a new token with the oldpwd variable
 * @return The new token OLDPWD=...
 */
static char	*set_var_oldpwd()
{
	char	*cwd;
	char	*tmp;
	char	*curr_pwd_text;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (NULL);
	tmp = ft_strdup("OLDPWD=");
	if (!tmp)
		return (free(cwd), NULL);
	curr_pwd_text = ft_strjoin(tmp, cwd);
	free(cwd);
	free(tmp);
	if (!curr_pwd_text)
		return (NULL);
	return (curr_pwd_text);
}

// Function to change the current working directory
int	sh_cd(t_app *app, char **cmd_args)
{
	char	*path;
	char	*old_pwd;

	//TESTING
	if (sh_pwd(app, cmd_args) == -1)
		return (-1);
	//END TESTING

	old_pwd = set_var_oldpwd();
	if (!old_pwd)
		return (-1); // malloc failed
	if (!cmd_args[1] || ft_strncmp(cmd_args[1], "~", 1) == 0)
		path = get_env_var("HOME", app->env);
	else if (ft_strncmp(cmd_args[1], "-", 1) == 0)
		path = get_env_var("OLDPWD", app->env);
	else
		path = cmd_args[1];
	if (chdir(path) == -1)
	{
		p(RED "cd: %s: No such file or directory\n" RST, cmd_args[1]);
		return (1);
	}

	//TESTING
	// the exit status of cd is now comming from pwd - because of this test
	if (sh_pwd(app, cmd_args) == -1)
		return (-1);
	//END TESTING

	if (get_env_var("OLDPWD", app->env))
	{
		if (handle_replace_export(app, old_pwd) == -1)
			return (-1);
	}
	else
	{
		if (handle_append_export(app, old_pwd) == -1)
			return (-1);
	}
	return (0);
}
