#include "../../include/minishell.h"

/**
 * @brief Extracts the value of an environment variable
 * from a string of the form "NAME=VALUE"
 * @return The value of the environment variable (NULL if not found)
 * it is the value after '=' character
*/
static char	*extract_env_var_val(const char *s)
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
			return *(extract_env_var_val(env[i]));
		i++;
	}
	return (NULL);
}
