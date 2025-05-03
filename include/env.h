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

#endif
