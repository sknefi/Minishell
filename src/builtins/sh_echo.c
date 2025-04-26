#include "../../include/minishell.h"

static int	is_n_flag(char *arg)
{
	size_t	i;
	size_t	arg_len;

	arg_len = strlen(arg);
	if (arg_len <= 1 || arg[0] != '-')
		return (false);
	i = 1;
	while (i < arg_len)
	{
		if (arg[i] != 'n')
			return (false);
		i++;
	}
	return (true);	
}

static int	count_chars(char **cmd_args)
{
	int		i;
	size_t	count;

	i = 0;
	count = 0;
	while (cmd_args[i])
	{
		count += ft_strlen(cmd_args[i]);
		i++;
	}
	return (count);
}

// Merge all arguments into one string
static char	*merge_args(char **cmd_args, int n_flag)
{
	int		i;
	char	*result;

	result = malloc(count_chars(cmd_args) + n_flag + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (cmd_args[i])
	{
		ft_strlcpy(result, cmd_args[i], ft_strlen(cmd_args[i]));
		i++;
	}
	if (n_flag)
		result[i] = '\n';
	return (result);
}

// Function to print the arguments passed to echo
int	sh_echo(t_app *app, char **cmd_args)
{
	int		i;
	int		n_flag;
	char	*result;

	(void)app;
	// set n_flag to true if there is -n flag
	// and break the loop if there is no more ARGS
	i = 0;
	n_flag = 0;
	while (cmd_args[i])
	{
		if (is_n_flag(cmd_args[i]))
			n_flag = 1;
		if (cmd_args[i + 1])
			break;
		i++;
	}

	// count how many characters are in the result (how much memory to allocate)
	result = merge_args(cmd_args, n_flag);
	if (!result)
		return (-1);
	p(result);
	free(result);
	return (0);
}
