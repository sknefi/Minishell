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
void show_env_prefix(char **env);

/**
 * @brief Creates an environment row with quotes
 * @param str The environment row
 * @return The environment row with quotes
 */
char	*create_env_row_with_quotes(char *str);

#endif
