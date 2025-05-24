/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkarika <fkarika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:07:55 by fkarika           #+#    #+#             */
/*   Updated: 2025/05/23 17:07:56 by fkarika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	sh_pwd(t_app *app, char **cmd_args)
{
	char	*cwd;

	(void)app;
	(void)cmd_args;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_printf("getcwd FAILED\n");
		return (ES_FAILED);
	}
	ft_printf("%s\n", cwd);
	free(cwd);
	return (ES_OK);
}
