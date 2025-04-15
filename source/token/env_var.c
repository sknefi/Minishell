#include "../minishell.h"

static char	*extract_env(const char *str);

char	*get_env_var(char *token)
{
	char	*env;
	char	*tmp;
	char	*result;
	int		i;

	result = ft_strdup("");
	i = 0;
	while (token[i])
	{
		if (token[i] == '$' && ft_isalpha(token[i + 1]))
		{
			tmp = extract_env(&token[i + 1]);
			env = getenv(tmp);
			if (env)
				result = ft_strjoin(result, env);
			free(tmp);
			while (token[i] && (ft_isalnum(token[i]) || token[i] == '_'))
				i++;
			}
		i++;
	}
	free(token);
	return (result);
}

static char	*extract_env(const char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	tmp = malloc(i + 1);
	if (!tmp)
		return (NULL);
	ft_strlcpy(tmp, str, i+1);
	return (tmp);
}
