/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkarika <fkarika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:23:28 by fkarika           #+#    #+#             */
/*   Updated: 2025/05/23 17:23:29 by fkarika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_redirection_out(t_app *app, t_ast_node *node)
{
	int			status;
	int			saved_stdout;
	t_ast_node	*cmd_node;

	saved_stdout = dup(STDOUT_FILENO);
	cmd_node = find_command_node(node);
	status = create_files(node, saved_stdout);
	if (status)
		return (status);
	status = exec_ast_node(cmd_node, app);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
	return (status);
}

int	handle_redirection_in(t_app *app, t_ast_node *node)
{
	int			fd;
	int			status;
	int			saved_stdin;
	t_ast_node	*cmd_node;

	fd = open(node->data[0], O_RDONLY);
	printf(Y "Opening file: %s\n" RST, node->data[0]);
	if (fd < 0)
	{
		ft_printf(RED "Error: cannot open file %s\n" RST, node->data[0]);
		return (1);
	}
	cmd_node = find_command_node(node);
	saved_stdin = dup(STDIN_FILENO);
	dup2(fd, STDIN_FILENO);
	close(fd);
	status = exec_ast_node(cmd_node, app);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
	return (status);
}
