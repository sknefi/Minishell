/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkarika <fkarika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:07:57 by fkarika           #+#    #+#             */
/*   Updated: 2025/05/23 19:58:45 by fkarika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Function to exit the shell
int	sh_exit(t_app *app, char **cmd_args)
{
	(void)app;
	(void)cmd_args;
	rl_clear_history();
	clean_app(app);
	ft_printf("exiting minishell\n");
	exit(ES_OK);
	return (ES_OK);
}
