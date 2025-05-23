/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkarika <fkarika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:17:40 by fkarika           #+#    #+#             */
/*   Updated: 2025/05/23 17:17:41 by fkarika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_builtin(t_app *app, char **cmd_args)
{
	int			i;
	char		*cmd_name;
	t_builtin	**builtins;

	i = 0;
	cmd_name = cmd_args[0];
	builtins = app->builtins;
	if (!cmd_args || !cmd_args[0])
		return (ES_OK);
	while (builtins[i])
	{
		if (ft_strcmp(builtins[i]->name, cmd_name) == 0)
			return (builtins[i]->f(app, cmd_args));
		i++;
	}
	return (NOT_BUILTIN);
}
