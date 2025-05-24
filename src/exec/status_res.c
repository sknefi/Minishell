/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_res.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkarika <fkarika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:17:36 by fkarika           #+#    #+#             */
/*   Updated: 2025/05/23 20:15:08 by fkarika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_child_exit_status(int status)
{
	int	sig;

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			return (ES_EXIT);
		if (sig == SIGQUIT)
			return (ES_SIGQUIT);
	}
	return (ES_OK);
}
