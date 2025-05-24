/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkarika <fkarika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:08:00 by fkarika           #+#    #+#             */
/*   Updated: 2025/05/23 19:58:23 by fkarika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Allocates a new token with the oldpwd variable
 * @return The new token OLDPWD=...
 */
static char	*set_var_oldpwd(void)
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

/**
 * Replaces the oldpwd variable with the new path
 * @param app The application structure
 * @param old_pwd The old path
 * @return -1 if malloc failed, 0 if success
 */
static int	replace_oldpwd(t_app *app, char *old_pwd)
{
	if (get_env_var("OLDPWD", app->env))
		return (handle_replace_export(app, old_pwd));
	else
		return (handle_append_export(app, old_pwd));
}

static char	*set_path(t_app *app, char **cmd_args)
{
	char	*path;

	if (cmd_args[1] && cmd_args[2])
	{
		ft_printf("cd: too many arguments\n");
		return (NULL);
	}
	else if (!cmd_args[1] || ft_strncmp(cmd_args[1], "~", 1) == 0)
		path = get_env_var("HOME", app->env);
	else if (ft_strncmp(cmd_args[1], "-", 1) == 0)
		path = get_env_var("OLDPWD", app->env);
	else
		path = cmd_args[1];
	return (path);
}

// Function to change the current working directory
int	sh_cd(t_app *app, char **cmd_args)
{
	int		result;
	char	*path;
	char	*old_pwd;

	old_pwd = set_var_oldpwd();
	if (!old_pwd)
		return (ES_FAILED);
	path = set_path(app, cmd_args);
	if (!path)
		return (free(old_pwd), ES_ERROR);
	if (chdir(path) == -1)
	{
		ft_printf("cd: %s: No such file or directory\n", cmd_args[1]);
		free(old_pwd);
		return (ES_ERROR);
	}
	result = replace_oldpwd(app, old_pwd);
	free(old_pwd);
	if (result == ES_FAILED)
		return (ES_FAILED);
	return (ES_OK);
}
