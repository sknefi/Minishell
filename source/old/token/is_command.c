#include "token.h"

int	is_command(char *str)
{
	if (ft_strcmp(str, "echo") == 0 || ft_strcmp(str, "cd") == 0 || ft_strcmp(str, "pwd") == 0 || ft_strcmp(str, "export") == 0 || 
			ft_strcmp(str, "unset") == 0 || ft_strcmp(str, "env") == 0 || ft_strcmp(str, "exit") == 0)
		return (1);
	return (0);
}
