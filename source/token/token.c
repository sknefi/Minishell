#include "../minishell.h"
#include <limits.h>

static int	tokenization(t_token **token, char *line);
static char	*extract_token(char *line, int *i);
static int	assign_type(char *token);
static char	*get_path();


int	prompt(t_token **token)
{
	char	*line;
	char	*shell_path;

	*token = NULL;
	line = NULL;
	shell_path = get_path();
	line = readline(shell_path);
	free(shell_path);
	if (!line)
		return (1);
	if (*line)
	{
		add_history(line);
		if (tokenization(token, line))
			return (1);
	}
	free(line);
	return (0);
}

static int	tokenization(t_token **token, char *line)
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
		if (NULL == tmp)
			return (1);
		if (ft_strchr(tmp, '$') && *tmp != '\'')
			tmp = get_env_var(tmp);
		type = assign_type(tmp);
		*token = token_append(*token, tmp, type);
		free(tmp);
	}
	return (0);
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
		if (line[*i + 1])
		{
			if (((line[*i] == '>' && line[*i + 1] == '>') || (line[*i] == '<' && line[*i + 1] == '<')))
			{
				if (line[*i + 2])
					(*i) += 2;
				else
				{
					ft_printf("Syntax error near unexpected token\n");
					return (NULL);
				}
			}
			else
				(*i)++;
		}
		else
		{
			ft_printf("Syntax error near unexpected token\n");
			return (NULL);
		}
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
	//if (is_command(token))
	//	return (TOKEN_COMMAND);
	if (!ft_strcmp(token, "|"))
		return (TOKEN_PIPE);
	else if (!ft_strcmp(token, ">"))
		return (TOKEN_REDIRECTION_OUT);
	else if (!ft_strcmp(token, "<"))
		return (TOKEN_REDIRECTION_IN);
	else if (!ft_strcmp(token, ">>"))
		return (TOKEN_APPEND);
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
