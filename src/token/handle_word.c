#include "../../include/minishell.h"

static void	handle_single_quotes(char *line, int *i, char **token, size_t *size);
static void	handle_double_quotes(char *line, int *i, char **token, size_t *size);
static void	expand_env(char *line, int *i, char **token, size_t *size);
static int	grow_token(char **token, size_t *size, char c);

char	*handle_word(char *line, int *i)
{
	char	*token;
	size_t		size;

	token = malloc(1);
	size = 0;
	if (!token)
		return (NULL);
	token[0] = '\0';
	while (line[*i] && !ft_isspace(line[*i]) && line[*i] != '|' && line[*i] != '<' && line[*i] != '>')
	{
		if (line[*i] == '\'')
			handle_single_quotes(line, i, &token, &size);
		else if (line[*i] == '\"')
			handle_double_quotes(line, i, &token, &size);
		else if (line[*i] == '$')
			expand_env(line, i, &token, &size);
		else
			if(grow_token(&token, &size, line[(*i)++]))
				return (NULL);
	}
	return (token);
}

static void	handle_single_quotes(char *line, int *i, char **token, size_t *size)
{
	(*i)++;
	while (line[*i] && line[*i] != '\'')
		grow_token(token, size, line[(*i)++]);
	if (line[*i] != '\'')
		ft_printf("Syntax error: quotes not closed honey\n");
	else
		(*i)++;
}

static void	handle_double_quotes(char *line, int *i, char **token, size_t *size)
{
	(*i)++;
	while (line[*i] && line[*i] != '\"')
	{
		if (line[*i] == '$')
			expand_env(line, i, token, size);
		else
			grow_token(token, size, line[(*i)++]);
	}
	if (line[*i] != '\"')
		ft_printf("Syntax error: quotes not closed honey\n");
	else
		(*i)++;
}

static void	expand_env(char *line, int *i, char **token, size_t *size)
{
	char	var_name[256];
	char	*val;
	int		j;

	j = 0;
	(*i)++;
	if (!ft_isalnum(line[*i]) && line[*i] != '_')
	{
		grow_token(token, size, '$');
		return ;
	}
	while (ft_isalnum(line[*i]) || line[*i] == '_')
	{
		if (j < 255)
			var_name[j++] = line[(*i)++];
		else
			(*i)++;
	}
	var_name[j] = '\0';
	val = getenv(var_name);
	j = 0;
	if (val)
	{
		while (val[j])
		{
			grow_token(token, size, val[j]);
			j++;
		}
	}
}

static int	grow_token(char **token, size_t *size, char c)
{
	char	*buffer;

	buffer = ft_realloc_token(*token, *size + 2);
	if (!buffer)
		return (1);
	*token = buffer;
	(*token)[(*size)++] = c;
	(*token)[(*size)] = '\0';
	return (0);
}
