#include "token.h"

int	is_command(char *str)
{
	if (ft_strcmp(str, "echo") || ft_strcmp(str, "cd") || ft_strcmp(str, "pwd") || ft_strcmp(str, "export") || 
			ft_strcmp(str, "unset") || ft_strcmp(str, "env") || ft_strcmp(str, "exit"))
		return (1);
	return (0);
}
