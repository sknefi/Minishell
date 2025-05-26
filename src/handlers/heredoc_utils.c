/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkarika <fkarika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:23:24 by fkarika           #+#    #+#             */
/*   Updated: 2025/05/26 14:54:56 by fkarika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

#define HEREDOC_INPUT "> "

extern volatile int	g_heredoc;

char	*read_heredoc_line(t_app *app)
{
	int		saved_stdout;
	char	*line;

	saved_stdout = dup(STDOUT_FILENO);
	if (app->term_stdout >= 0)
		dup2(app->term_stdout, STDOUT_FILENO);
	line = readline(HEREDOC_INPUT);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
	if (g_heredoc)
	{
		if (line)
			free(line);
		return (NULL);
	}
	return (line);
}

void	process_heredoc_line(char *line, t_input *input,
	int pipe_write, t_app *app)
{
	char	*expanded_line;

	ft_memset(input, 0, sizeof(t_input));
	input->line = ft_strdup(line);
	free(line);
	expanded_line = handle_word(input, app);
	write(pipe_write, expanded_line, ft_strlen(expanded_line));
	write(pipe_write, "\n", 1);
	free(expanded_line);
	free(input->line);
}

void	heredoc_child_cleanup(int pipe_write, t_app *app)
{
	close(pipe_write);
	rl_clear_history();
	clean_app(app);
	if (g_heredoc)
	{
		write(1, "\n", 1);
		exit(130);
	}
	exit(0);
}
