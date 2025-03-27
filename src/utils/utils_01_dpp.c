#include "../../include/minishell.h"
// utils for double pointer functions

size_t	count_pointer(char **str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	free_dpp_i(char **str, int i)
{
	while (i >= 0)
		free(str[i--]);
	free(str);
}

void	free_dpp(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}
