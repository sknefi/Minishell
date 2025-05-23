/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkarika <fkarika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:23:29 by fkarika           #+#    #+#             */
/*   Updated: 2025/05/23 19:59:56 by fkarika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Redirect stdout to the top file
 * @param node The node to redirect stdout to
 * @param saved_stdout The saved stdout file descriptor
 * @return 0 on success, 1 on failure
 */
static int	redirect_stdout(t_ast_node *node, int saved_stdout)
{
	int	fd;

	if (node->type == NODE_REDIRECTION_OUT)
		fd = open(node->data[0], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else
		fd = open(node->data[0], O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd < 0)
	{
		ft_printf("Error: cannot open file %s\n", node->data[0]);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int	is_redirection_out(t_ast_node *node)
{
	return (node->type == NODE_REDIRECTION_OUT || node->type == NODE_APPEND);
}

t_ast_node	*find_command_node(t_ast_node *node)
{
	t_ast_node	*current;

	current = node;
	while (current && current->right && is_redirection_out(current->right))
		current = current->right;
	return (current->right);
}

int	create_files(t_ast_node *node, int saved_stdout)
{
	int			fd;
	t_ast_node	*current;

	if (redirect_stdout(node, saved_stdout))
		return (1);
	current = node->right;
	while (current && (current->type == NODE_REDIRECTION_OUT
			|| current->type == NODE_APPEND))
	{
		if (current->type == NODE_REDIRECTION_OUT)
			fd = open(current->data[0], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		else
			fd = open(current->data[0], O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (fd < 0)
		{
			ft_printf("Error: cannot open file %s\n", current->data[0]);
			dup2(saved_stdout, STDOUT_FILENO);
			close(saved_stdout);
			return (1);
		}
		close(fd);
		current = current->right;
	}
	return (0);
}
