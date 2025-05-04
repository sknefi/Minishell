/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmateja <tmateja@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:03:49 by tmateja           #+#    #+#             */
/*   Updated: 2025/05/04 16:05:31 by tmateja          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	tokenization(t_token **token, char *line);
static char	*extract_token(char *line, int *i);
static int	assign_type(char *token);
static char	*get_path(void);

int	prompt(t_token **token, t_ast_node **node)
{
	char	*line;
	char	*shell_path;

	*token = NULL;
	line = NULL;
	shell_path = get_path();
	line = readline(shell_path);
	free(shell_path);
	if (!line)
	{
		free(line);
		free_ast(*node);
		exit(EXIT_SUCCESS);
	}
	if (*line)
	{
		add_history(line);
		if (tokenization(token, line))
		{
			free(line);
			return (1);
		}
	}
	free(line);
	return (0);
}

static int	tokenization(t_token **token, char *line)
{
	int		i;
	int		type;
	char	*tmp;

	i = 0;
	while (line[i])
	{
		while (line[i] && ft_isspace(line[i]))
			i++;
		if (!line || !line[i])
			break ;
		tmp = extract_token(line, &i);
		if (NULL == tmp)
			return (1);
		type = assign_type(tmp);
		*token = token_append(*token, tmp, type);
		free(tmp);
	}
	return (0);
}

static char	*extract_token(char *line, int *i)
{
	char	*token;

	token = NULL;
	if (line[*i] == '|' || line[*i] == '<' || line[*i] == '>')
		token = handle_operators(line, i);
	else
		token = handle_word(line, i);
	if (!token)
		return (NULL);
	return (token);
}

static int	assign_type(char *token)
{
	if (!ft_strcmp(token, "|"))
		return (TOKEN_PIPE);
	else if (!ft_strcmp(token, ">"))
		return (TOKEN_REDIRECTION_OUT);
	else if (!ft_strcmp(token, "<"))
		return (TOKEN_REDIRECTION_IN);
	else if (!ft_strcmp(token, ">>"))
		return (TOKEN_APPEND);
	else if (!ft_strcmp(token, "<<"))
		return (TOKEN_HEREDOC);
	return (TOKEN_WORD);
}

static char	*get_path(void)
{
	char	*str;
	char	*tmp;

	tmp = getcwd(NULL, 0);
	if (!tmp)
		exit(EXIT_FAILURE);
	str = ft_strjoin(tmp, "$ ");
	if (!str)
	{
		free(tmp);
		exit(EXIT_FAILURE);
	}
	free(tmp);
	return (str);
}
