#ifndef UTILS_H
# define UTILS_H
# include "minishell.h"

/**
 * @brief Counts the number of pointers in an array of pointers
 * @param str The array of pointers
 * @return The number of pointers in the array
*/
size_t	count_pointer(char **str);

/**
 * @brief Frees an array of pointers, from the last pointer to the first
 * and the array itself
 * @param str The array of pointers
 * @param i The number of pointers to free
*/
void	free_dpp_i(char **str, int i);

/**
 * @brief Frees an array of pointers and the array itself
 * @param str The array of pointers
 */
void	free_dpp(char **str);

/**
 * @brief Checks if a string contains an equal sign
 * @param str The string to check
 * @return 1 if the string contains an equal sign, 0 otherwise
 */
int	contains_equal_sign(char *str);

#endif