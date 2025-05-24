/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkarika <fkarika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:18:45 by fkarika           #+#    #+#             */
/*   Updated: 2025/05/23 17:18:46 by fkarika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

#define NO_OF_BUILTINS 7

/**
 * @brief Initialize one builtin with name and function
*/
static t_builtin	
	*init_one_builtin(char *name, int (*f)(t_app *app, char **cmd_args))
{
	t_builtin	*builtin;

	builtin = malloc(sizeof(t_builtin));
	if (!builtin)
		return (NULL);
	builtin->name = name;
	builtin->f = f;
	return (builtin);
}

void	free_builtins(t_builtin **builtins)
{
	int	i;

	if (!builtins)
		return ;
	i = 0;
	while (builtins[i])
	{
		free(builtins[i]);
		i++;
	}
	free(builtins);
}

/**
 * @brief Initialize additional builtins
 * I love norminette
 */
t_builtin	**init_additional_builtins(t_builtin **builtins)
{
	builtins[3] = init_one_builtin("export", sh_export);
	if (!builtins[3])
		return (free_builtins(builtins), NULL);
	builtins[4] = init_one_builtin("unset", sh_unset);
	if (!builtins[4])
		return (free_builtins(builtins), NULL);
	builtins[5] = init_one_builtin("env", sh_env);
	if (!builtins[5])
		return (free_builtins(builtins), NULL);
	builtins[6] = init_one_builtin("exit", sh_exit);
	if (!builtins[6])
		return (free_builtins(builtins), NULL);
	builtins[7] = NULL;
	return (builtins);
}

t_builtin	**init_builtins(void)
{
	t_builtin	**builtins;

	builtins = malloc(sizeof(t_builtin *) * (NO_OF_BUILTINS + 1));
	if (!builtins)
		return (NULL);
	builtins[0] = init_one_builtin("echo", sh_echo);
	if (!builtins[0])
		return (free_builtins(builtins), NULL);
	builtins[1] = init_one_builtin("pwd", sh_pwd);
	if (!builtins[1])
		return (free_builtins(builtins), NULL);
	builtins[2] = init_one_builtin("cd", sh_cd);
	if (!builtins[2])
		return (free_builtins(builtins), NULL);
	builtins = init_additional_builtins(builtins);
	if (!builtins)
		return (free_builtins(builtins), NULL);
	return (builtins);
}
