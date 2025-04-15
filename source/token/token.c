#include "../minishell.h"
#include <limits.h>

static void	tokenization(t_token **token, char *line);
static char	*extract_token(char *line, int *i);
static int	assign_type(char *token);
static char	*get_path();


void	prompt(t_token **token)
{
	char	*line;
	char	*shell_path;

	*token = NULL;
	line = NULL;
	shell_path = get_path();
	line = readline(shell_path);
	free(shell_path);
	if (!line)
		return ;
	if (*line)
	{
		add_history(line);
		tokenization(token, line);
	}
	free(line);
}

static void	tokenization(t_token **token, char *line)
{
	int		i;
	int		type;
	char	*tmp;

	i = 0;
	while (line[i])
	{
		while (line[i] && ft_isspace(line[i]))
			i++;
		if (!line || !line[i])
			break ;
		tmp = extract_token(line, &i);
		if (ft_strchr(tmp, '$') && *tmp != '\'')
			tmp = get_env_var(tmp);
		type = assign_type(tmp);
		*token = token_append(*token, tmp, type);
		free(tmp);
	}
}

static char	*extract_token(char *line, int *i)
{
	int		start;
	char	quote;
	char	*token;

	start = *i;
	if (line[*i] == '\'' || line[*i] == '"')
	{
		quote = line[*i];
		(*i)++;
		while (line[*i] && line[*i] != quote)
			(*i)++;
		if (line[*i] == quote)
			(*i)++;
	}
	else if (line[*i] == '|' || line[*i] == '<' || line[*i] == '>')
	{
		if ((line[*i] == '>' && line[*i + 1] == '>') || (line[*i] == '<' && line[*i + 1] == '<'))
			(*i) += 2;
		else
			(*i)++;
	}
	else
	{
		while (line[*i] && !ft_isspace(line[*i]) && line[*i] != '|' && line[*i] != '<' && line[*i] != '>')
			(*i)++;
	}
	token = ft_substr(line, start, *i - start);
	if (!token)
		return (NULL);
	return (token);
}

static int	assign_type(char *token)
{
	if (is_command(token))
		return (TOKEN_COMMAND);
	else if (!ft_strcmp(token, "|"))
		return (TOKEN_PIPE);
	else if (!ft_strcmp(token, ">"))
		return (TOKEN_REDIRECTION_IN);
	else if (!ft_strcmp(token, "<"))
		return (TOKEN_REDIRECTION_OUT);
	else if (!ft_strcmp(token, ">>"))
		return (TOKEN_HEREDOC);
	else if (!ft_strcmp(token, "<<"))
		return (TOKEN_HEREDOC);
	return (TOKEN_WORD);
}

static char	*get_path()
{
	char	*str;
	char	*tmp;

	tmp = malloc(PATH_MAX); //PATH_MAX is not always good, need to check on it
	if (!tmp)
		exit(EXIT_FAILURE);
	getcwd(tmp, PATH_MAX); //TODO getcwd failure
	str = ft_strjoin(tmp, "$ ");
	free(tmp);
	return (str);
}
