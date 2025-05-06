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

static int	count_chars(char **cmd_args, int start)
{
	int		i;
	size_t	count;

	i = start;
	count = 0;
	while (cmd_args[i])
	{
		count += ft_strlen(cmd_args[i]);
		i++;
	}
	return (count);
}

// Merge all arguments into one string
static char	*merge_args(char **cmd_args, int start, int n_flag)
{
	int		i;
	char	*result;
	size_t	pos;

	int count = count_chars(cmd_args, start) - n_flag + 1;
	result = ft_calloc(count, sizeof(char));
	if (!result)
		return (NULL);
	i = start;
	pos = 0;
	while (cmd_args[i])
	{
		ft_strlcpy(result + pos, cmd_args[i], ft_strlen(cmd_args[i]) + 1);
		pos += ft_strlen(cmd_args[i]);
		if (cmd_args[i + 1])
			result[pos++] = ' ';
		i++;
	}
	if (!n_flag)
		result[pos] = '\n';
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
	i = 1; // after the echo word
	n_flag = 0;
	while (cmd_args[i])
	{
		if (is_n_flag(cmd_args[i]))
			n_flag = 1;
		else
			break ;
		i++;
	}
	result = merge_args(cmd_args, i, n_flag);
	if (!result)
		return (ES_FAILED);
	ft_printf("%s", result);
	free(result);
	return (ES_OK);
}
