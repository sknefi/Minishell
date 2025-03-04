#include "../minishell.h"
#include "token.h"
#include <linux/limits.h>
#include <stdio.h>
#include <string.h>
#include "../../libft_divinus/libft.h"

static void	tokenization(t_token **token, char *line);
static char	*extract_token(char *line, int *i);
static int	assign_type(char *token);

void	lexer(t_token **token)
{
	char	*line;

	*token = NULL;
	line = NULL;
	char s[PATH_MAX];
	getcwd(s, sizeof(s));
	line = readline(s);
	if (!line)
		return ;
	if (*line)
	{
		printf("%s\n", line);
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
			break;
		tmp = extract_token(line, &i); //TODO
		if (!tmp || !*tmp)
		{
			free(tmp);
			break;
		}
		if (ft_strchr(tmp, '$'))
				tmp = get_env_var(tmp); //TODO
		type = assign_type(tmp); //TODO
		*token = token_append(*token, tmp, type);
		free(tmp);
		if (line[i] != '\0')
			i++;
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
		while (line[*i] && line[*i] != quote)
			(*i)++;
		if (line[*i] == quote)
			(*i)++;
	}
	else
	{
		while (line[*i] && !ft_isspace(line[*i]))
			(*i)++;
	}
	token = ft_substr(line, start, *i - start);
	if (!token)
		return (NULL);
	return (token);
}

static int	assign_type(char *token)
{
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

