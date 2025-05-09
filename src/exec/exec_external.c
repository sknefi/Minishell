#include "../../include/minishell.h"

static char	*get_cmd_path(t_app *app, char **cmd_args)
{
	int		i;
	char	*path;
	char	**all_paths;
	char	*cmd_path;
	char	*tmp;
	
	path = get_env_var("PATH", app->env);
	if (!path)
		return (NULL);
	all_paths = ft_split(path, ':');
	if (!all_paths)
		return (NULL);
	i = 0;
	while (all_paths[i])
	{
		cmd_path = ft_strjoin(all_paths[i], "/");
		if (!cmd_path)
		{
			free_dpp(all_paths);
			return (NULL);
		}
		tmp = ft_strjoin(cmd_path, cmd_args[0]);
		free(cmd_path);
		if (!tmp)
		{
			free_dpp(all_paths);
			return (NULL);
		}
		if (access(tmp, F_OK | X_OK) == 0)
		{
			free_dpp(all_paths);
			return (tmp);
		}
		free(tmp);
		i++;
	}
	free_dpp(all_paths);
	return (NULL);
}

int	exec_external(t_app *app, char **cmd_args)
{
	char	*cmd_path;
	pid_t	pid;
	int		status;

	cmd_path = get_cmd_path(app, cmd_args);
	if (!cmd_path)
		return (1);
	ft_printf(Y "cmd_path: %s\n" RST, cmd_path);
	
	pid = fork();
	if (pid < 0)
	{
		ft_printf(RED "Error: fork failed\n" RST);
		free(cmd_path);
		return (1);
	}
	
	if (pid == 0)  // Child process
	{
		execve(cmd_path, cmd_args, app->env);
		// If execve returns, it means there was an error
		ft_printf(RED "Error: execve failed\n" RST);
		free(cmd_path);
		exit(1); // Exit the child process
	}
	
	// Parent process
	waitpid(pid, &status, 0);
	free(cmd_path);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1); // Return 1 if the child process did not exit correctly
}
