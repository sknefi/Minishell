#include "../minishell.h"

static int	tokenization(t_token **token, char *line);
static char	*extract_token(char *line, int *i);
static int	assign_type(char *token);
static char	*get_path();


int	prompt(t_token **token, t_ast_node **node)
{
	char	*line;
	char	*shell_path;

	*token = NULL;
	line = NULL;
	shell_path = get_path();
	line = readline(shell_path);
	free(shell_path);
	if (!line)
	{
		free(line);
		write(1, "exit\n", 5);
		free_ast(*node);
		exit(EXIT_SUCCESS);
	}
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


void	remove_quotes(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (NULL == str)
		return ;
	while (str[i] != '\0')
	{
		if (str[i] != '\'' && str[i] != '\"')
		{
			str[j] = str[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
}

static char	*extract_token(char *line, int *i)
{
	int		start;
	char	quote;
	char	*token;

	quote = 0;
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
		token = ft_substr(line, start, *i - start);
		remove_quotes(token);
		return (token);
	}
	if (quote == 0)
		token = ft_substr(line, start, *i - start);
	else
		token = ft_substr(line, start + 1, *i - start - 2);
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
	//else if (ft_strchr(token, 34))
	//	return (TOKEN_SINGLE_QUOTES);
	return (TOKEN_WORD);
}

static char	*get_path()
{
	char	*str;
	char	*tmp;

	tmp = getcwd(NULL, 0);
	if (!tmp)
		exit(EXIT_FAILURE);
	str = ft_strjoin(tmp, "$ ");
	if (!str)
	{
		free(tmp);
		exit(EXIT_FAILURE);
	}
	free(tmp);
	return (str);
}
