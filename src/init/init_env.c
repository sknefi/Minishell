/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkarika <fkarika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:18:44 by fkarika           #+#    #+#             */
/*   Updated: 2025/05/23 17:18:45 by fkarika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_env(char **env)
{
	int		i;

	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

char	**init_env(char **env)
{
	int		i;
	int		env_size;
	char	**new_env;

	env_size = count_pointer(env);
	new_env = malloc(sizeof(char *) * (env_size + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
			return (NULL);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}
