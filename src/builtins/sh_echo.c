#include "../../include/minishell.h"

/**
 * @brief Check if the argument is a -n flag
 * @param arg The argument to check
 * @return true if the argument is a -n flag, false otherwise
 */
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

/**
 * @brief Count the number of characters in the arguments
 * @param cmd_args All arguments
 * @param start The index of the first argument (after -n flags)
 * @param n_flag The flag to check if the -n flag is set
 * @return The number of characters in the arguments
 */
static size_t	count_chars(char **cmd_args, int start, int n_flag)
{
	int		i;
	size_t	count;

	count = 0;
	i = start;
	while (cmd_args[i])
	{
		count += ft_strlen(cmd_args[i]);
		if (cmd_args[i + 1])
			count += 1;
		i++;
	}
	if (!n_flag)
		count += 1;
	return (count);
}

/**
 * @brief Copy the arguments to the result string
 * @param res The result string (allocated with count_chars)
 * @param cmd_args All arguments
 * @param start The index of the first argument (after -n flags)
 * @param n_flag The flag to check if the -n flag is set
 */
static void	copy_args(char *res, char **cmd_args, int start, int n_flag)
{
	int		i;
	int		pos;
	size_t	len;

	i = start;
	pos = 0;
	while (cmd_args[i])
	{
		len = ft_strlen(cmd_args[i]);
		ft_strlcpy(res + pos, cmd_args[i], len + 1);
		pos += len;
		if (cmd_args[i + 1])
			res[pos++] = ' ';
		i++;
	}
	if (!n_flag)
		res[pos++] = '\n';
	res[pos] = '\0';
}

/**
 * @brief Merge the arguments into a single string
 * @param cmd_args All arguments
 * @param start The index of the first argument (after -n flags)
 * @param n_flag The flag to check if the -n flag is set
 * @return The merged string
 */
static char	*merge_args(char **cmd_args, int start, int n_flag)
{
	char	*result;
	size_t	total_len;

	total_len = count_chars(cmd_args, start, n_flag);
	result = ft_calloc(total_len, sizeof(char));
	if (!result)
		return (NULL);
	copy_args(result, cmd_args, start, n_flag);
	return (result);
}

int	sh_echo(t_app *app, char **cmd_args)
{
	int		i;
	int		n_flag;
	char	*result;

	(void)app;
	i = 1;
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
