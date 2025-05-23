/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkarika <fkarika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:08:08 by fkarika           #+#    #+#             */
/*   Updated: 2025/05/23 17:08:09 by fkarika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

/**
 * @brief Initializes the environment variables
 * @param env The environment variables
 * @return The initialized environment variables on heap
*/
char	**init_env(char **env);

/**
 * @brief Frees the environment variables
 * @param env The environment variables
 */
void	free_env(char **env);

/**
 * @brief Shows the environment variables with the prefix "declare -x " 
 * - bash behavior
 * @param env The environment variables
 */
void	show_env_prefix(char **env);

/**
 * @brief Sorts the environment variables
 * @param env The environment variables
 * @return The sorted environment variables on heap
 */
char	**env_sort(char **env);

#endif
