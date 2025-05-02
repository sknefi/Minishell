#include "../minishell.h"

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
			if(!grow_token(&token, &size, line[*i++]))
				return (NULL);
	}
	return (token);
}

static void	handle_single_quotes(char *line, int *i, char **token, size_t *size)
{
	(*i)++;
	while (line[*i] && line[*i] != '\'')
		grow_token(*token, size, line[*i++]);
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
			expand_env(line, i, *token, size);
		else
			grow_token(*token, size, line[*i++])
	}
	if (line[*i] != '\"')
		ft_printf("Syntax error: quotes not closed honey\n");
	else
		(*i)++;
}

static void	expand_env(char *line, int *i, char **token, size_t *size)
{
	(*i)++;
}

static int	grow_token(char **token, size_t *size, char c)
{
	char	*buffer;

	buffer = realloc(*token, *size + 2);
	if (!buffer)
		return (1);
	*token = buffer;
	(*token)[(*size)++] = c;
	(*token)[(*size)] = '\0';
	return (0);
}
