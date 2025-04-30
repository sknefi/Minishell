#include "../minishell.h"
char *ft_strjoin_free(char *s1, char *s2)
{
    char *result;
    
    if (!s1 || !s2)
        return (NULL);
    result = ft_strjoin(s1, s2);
    free(s1);
    return (result);
}

char	*handle_quotes(char *line, int *i)
{
	int		start;
	char	quote;
	char	*token;

	token = NULL;
	quote = 0;
	start = *i;
	if (line[*i] == '\'' || line[*i] == '"')
	{
		quote = line[*i];
		(*i)++;
		while (line[*i] && line[*i] != quote)
			(*i)++;
		if (!line[*i])
		{
			ft_printf("Syntax error: quotes not closed honey\n");
			return (NULL);
		}
		(*i)++;
		if ('"' == quote)
		{
			token = ft_substr(line, start + 1, *i - start - 2);
			token = get_env_var(token);
		}
		else
			token = ft_substr(line, start + 1, *i - start - 2);
	}
	return (token);
}

char	*handle_operators(char *line, int *i)
{
	int		start;
	char	*token;

	start = *i;
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
	token = ft_substr(line, start, *i - start);
	return (token);
}

char	*handle_word(char *line, int *i)
{
    int buffer_size = 256;
    char *buffer = malloc(buffer_size);
    int pos = 0;
    if (!buffer) return NULL;

    while (line[*i] != '\0' && !isspace(line[*i])) {
        if (pos >= buffer_size - 1) {
            buffer_size *= 2;
            char *new_buffer = realloc(buffer, buffer_size);
            if (!new_buffer) {
                free(buffer);
                return NULL;
            }
            buffer = new_buffer;
        }

        if (line[*i] == '"') {
            (*i)++;
            while (line[*i] != '"' && line[*i] != '\0') {
                if (line[*i] == '$') {
                    int next_i = *i + 1;
                    if (isalpha(line[next_i]) || line[next_i] == '_') {
                        (*i)++;
                        char var_name[256];
                        int j = 0;
                        
                        while (isalnum(line[*i]) || line[*i] == '_') {
                            if (j < 255)
								var_name[j++] = line[(*i)++];
                            else (*i)++;
                        }
                        var_name[j] = '\0';
                        
                        char *val = getenv(var_name);
                        if (val) {
                            int val_len = strlen(val);
                            while (pos + val_len >= buffer_size - 1) {
                                buffer_size *= 2;
                                char *new_buf = realloc(buffer, buffer_size);
                                if (!new_buf) {
                                    free(buffer);
                                    return NULL;
                                }
                                buffer = new_buf;
                            }
                            strcpy(buffer + pos, val);
                            pos += strlen(val);
                        }
                    } else {
                        buffer[pos++] = line[(*i)++];
                    }
                } else {
                    buffer[pos++] = line[(*i)++];
                }
            }
            if (line[*i] == '"')
				(*i)++;
        } else if (line[*i] == '$') {
            int next_i = *i + 1;
            if (isalpha(line[next_i]) || line[next_i] == '_') {
                (*i)++;
                char var_name[256];
                int j = 0;
                
                while (isalnum(line[*i]) || line[*i] == '_') {
                    if (j < 255)
						var_name[j++] = line[(*i)++];
                    else (*i)++;
                }
                var_name[j] = '\0';
                
                char *val = getenv(var_name);
                if (val) {
                    int val_len = strlen(val);
                    while (pos + val_len >= buffer_size - 1) {
                        buffer_size *= 2;
                        char *new_buf = realloc(buffer, buffer_size);
                        if (!new_buf) {
                            free(buffer);
                            return NULL;
                        }
                        buffer = new_buf;
                    }
                    strcpy(buffer + pos, val);
                    pos += strlen(val);
                }
            } else {
                buffer[pos++] = line[(*i)++];
            }
        } else {
            buffer[pos++] = line[(*i)++];
        }
    }

    buffer[pos] = '\0';
    return buffer;
}
