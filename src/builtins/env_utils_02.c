// #include "../../include/minishell.h"

// char	*create_env_row_with_quotes(char *str)
// {
// 	int		i;
// 	int		j;
// 	char	*new_str;

// 	i = 0;
// 	while (str[i] && str[i] != '=')
// 		i++;
// 	new_str = (char *)malloc(sizeof(char) * (ft_strlen(str) + 3));
// 	if (!new_str)
// 		return (NULL);
// 	j = 0;
// 	while (j < i)
// 	{
// 		new_str[j] = str[j];
// 		j++;
// 	}
// 	if (str[i] == '=')
// 	{
// 		new_str[j++] = '=';
// 		new_str[j++] = '"';
// 		i++;
// 		while (str[i])
// 			new_str[j++] = str[i++];
// 		new_str[j++] = '"';
// 	}
// 	new_str[j] = '\0';
// 	return (new_str);
// }
