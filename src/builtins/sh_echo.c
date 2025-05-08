#include "../../include/minishell.h"
static int  is_n_flag(char *arg)
{
	size_t  i;
	size_t  arg_len;
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
// static int   count_chars(char **cmd_args, int start)
// {
//  int     i;
//  size_t  count;
//  i = start;
//  count = 0;
//  while (cmd_args[i])
//  {
//      count += ft_strlen(cmd_args[i]);
//      i++;
//  }
//  return (count);
// }
static char *merge_args(char **cmd_args, int start, int n_flag)
{
	int		i;
	char	*result;
	size_t	pos;
	size_t	total_len;
	// Step 1: Calculate total length needed for result
	total_len = 0;
	i = start;
	while (cmd_args[i])
	{
		total_len += ft_strlen(cmd_args[i]);
		if (cmd_args[i + 1])
			total_len += 1; // for space
		i++;
	}
	if (!n_flag)
		total_len += 1; // for final newline
	total_len += 1; // for null terminator
	// Step 2: Allocate memory
	result = ft_calloc(total_len, sizeof(char));
	if (!result)
		return (NULL);
	// Step 3: Copy arguments to result string
	i = start;
	pos = 0;
	while (cmd_args[i])
	{
		size_t len = ft_strlen(cmd_args[i]);
		ft_strlcpy(result + pos, cmd_args[i], len + 1);
		pos += len;
		if (cmd_args[i + 1])
			result[pos++] = ' ';
		i++;
	}
	// Step 4: Add newline if no -n
	if (!n_flag)
		result[pos++] = '\n';
	// Step 5: Null terminate
	result[pos] = '\0';
	return (result);
}
// Function to print the arguments passed to echo
int sh_echo(t_app *app, char **cmd_args)
{
	int     i;
	int     n_flag;
	char    *result;
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