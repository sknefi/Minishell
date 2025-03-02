#include "../minishell.h"
#include <linux/limits.h>
#include <stdio.h>
#include <string.h>

static void	tokenization(t_token *token, char *line);

void	lexer(void)
{
	t_token	*token;
	char	*line;

	token = NULL;
	line = NULL;
	char s[PATH_MAX];
	getcwd(s, sizeof(s));
	line = readline(s);
	if (!line)
		return ;
	if (*line)
	{
		add_history(line);
		tokenization(token, line);
	}
	free(line);
}

static void	tokenization(t_token *token, char *line)
{
	int		i;
	char	*tmp;

	i = 0;
	while (line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		if (!line)
			break;
		tmp = extract_token(line, &i); //TODO
		if (!tmp)
			break;
		if (ft_strchr(tmp, '$')
				tmp = var(); //TODO
		type = assign_type(); //TODO
		token_append(token, *line, type);
		i++;
	}
} 
