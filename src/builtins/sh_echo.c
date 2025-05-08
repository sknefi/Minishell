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
	int		arg_count;
	size_t	total_len;

	// Count number of arguments
	arg_count = 0;
	i = start;
	while (cmd_args[i++])
		arg_count++;
	
	// Calculate total length: sum of arg lengths + spaces between args + newline if needed
	total_len = count_chars(cmd_args, start);
	if (arg_count > 1)
		total_len += (arg_count - 1); // Add spaces between arguments
	if (!n_flag)
		total_len += 1; // Add space for newline character
	
	// Allocate memory with one extra byte for null terminator
	result = ft_calloc(total_len + 1, sizeof(char));
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
