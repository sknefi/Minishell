/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkarika <fkarika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:17:38 by fkarika           #+#    #+#             */
/*   Updated: 2025/05/26 17:10:50 by fkarika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <signal.h>

int	exec_ast_node(t_ast_node *node, t_app *app)
{
	int	status;

	if (!node)
		return (0);
	if (node->type == NODE_CMD)
	{
		status = exec_builtin(app, node->data);
		if (status == NOT_BUILTIN)
			status = exec_external(app, node->data);
		return (status);
	}
	else if (node->type == NODE_REDIRECTION_IN)
		return (handle_redirection_in(app, node));
	else if (node->type == NODE_REDIRECTION_OUT)
		return (handle_redirection_out(app, node));
	else if (node->type == NODE_APPEND)
		return (handle_redirection_out(app, node));
	else if (node->type == NODE_HEREDOC)
		return (handle_heredoc(app, node));
	else if (node->type == NODE_PIPE)
		return (handle_pipe(app, node));
	return (ES_ERROR);
}

int	sh_exec(t_app *app)
{
	int	status;

	if (!app->root)
		return (ES_ERROR);
	ignore_int_quit();
	status = exec_ast_node(app->root, app);
	sig_handler();
	if (status == ES_CMD_NOT_FOUND && app->root->data && app->root->data[0])
		ft_printf("%s: command not found\n", app->root->data[0]);
	app->exit_status = status;
	return (status);
}
