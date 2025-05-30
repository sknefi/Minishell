/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkarika <fkarika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:17:39 by fkarika           #+#    #+#             */
/*   Updated: 2025/05/26 17:11:08 by fkarika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Get all paths from PATH environment variable
 * @param app The application
 * @return Array of paths or NULL if error
 */
static char	**get_all_paths(t_app *app)
{
	char	*path;
	char	**all_paths;

	path = get_env_var("PATH", app->env);
	if (!path)
		return (NULL);
	all_paths = ft_split(path, ':');
	return (all_paths);
}

/**
 * @brief Find the executable path for a command
 * @param all_paths Array of paths to search in
 * @param cmd Command to find
 * @return Full path to executable or NULL if not found
 */
static char	*find_executable(char **all_paths, char *cmd)
{
	int		i;
	char	*tmp;
	char	*cmd_path;

	if (!all_paths || !cmd)
		return (NULL);
	i = 0;
	while (all_paths[i])
	{
		cmd_path = ft_strjoin(all_paths[i], "/");
		if (!cmd_path)
			return (NULL);
		tmp = ft_strjoin(cmd_path, cmd);
		free(cmd_path);
		if (!tmp)
			return (NULL);
		if (access(tmp, F_OK | X_OK) == 0)
			return (tmp);
		free(tmp);
		i++;
	}
	return (NULL);
}

/**
 * @brief Get the path of executable command if exists 
 * from the PATH environment variable
 * @param app - app struct
 * @param cmd_args - command arguments
 * @return char* - path of executable command if exists, NULL otherwise
 */
static char	*get_cmd_path(t_app *app, char **cmd_args)
{
	char	*executable_path;
	char	**all_paths;

	all_paths = get_all_paths(app);
	if (!all_paths)
		return (NULL);
	executable_path = find_executable(all_paths, cmd_args[0]);
	free_dpp(all_paths);
	return (executable_path);
}

/**
 * @brief Choose the path of the command, if the 
 * command is a path, return the path, 
 * otherwise return the path from the PATH environment variable
 * @param app - app struct
 * @param cmd_args - command arguments
 * @return char* - path of the command
 */
static char	*choose_cmd_path(t_app *app, char **cmd_args)
{
	if ((cmd_args[0][0] == '/' || cmd_args[0][0] == '.')
			&& access(cmd_args[0], F_OK | X_OK) == 0)
		return (ft_strdup(cmd_args[0]));
	return (get_cmd_path(app, cmd_args));
}

int	exec_external(t_app *app, char **cmd_args)
{
	int		status;
	int		wstatus;
	char	*cmd_path;
	pid_t	pid;

	cmd_path = choose_cmd_path(app, cmd_args);
	if (!cmd_path)
		return (ES_CMD_NOT_FOUND);
	pid = fork();
	if (pid < 0)
		return (free(cmd_path), ft_printf("Error: fork failed\n"), ES_ERROR);
	if (pid == 0)
	{
		default_int_quit();
		execve(cmd_path, cmd_args, app->env);
		free(cmd_path);
		clean_app(app);
		exit(EXIT_FAILURE);
	}
	waitpid(pid, &wstatus, 0);
	free(cmd_path);
	status = get_child_exit_status(wstatus);
	if (status != CHILD_NO_STATUS)
		return (status);
	return (ES_ERROR);
}
