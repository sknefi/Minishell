/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkarika <fkarika@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 20:47:33 by tmateja           #+#    #+#             */
/*   Updated: 2025/05/26 12:35:11 by fkarika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/*
 * Takes root node.
 * Free all nodes, by going to the left and right.
 */

void	free_ast(t_ast_node *node)
{
	int	i;

	if (!node)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	if (node->data)
	{
		i = 0;
		while (node->data[i])
		{
			free(node->data[i]);
			i++;
		}
		free(node->data);
	}
	free(node);
}
