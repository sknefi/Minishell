/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkarika <fkarika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:08:02 by fkarika           #+#    #+#             */
/*   Updated: 2025/05/23 17:08:03 by fkarika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include <stdio.h>
# include "structs.h"

int		prompt(t_app *app, t_input *input);
char	*handle_operators(t_input *input, t_app *app);
char	*handle_word(t_input *input, t_app *app);
int		grow_token(t_app *app, char **token, size_t *size, char c);
int		expand_env(t_input *input, char **token, size_t *size, t_app *app);
int		expand_exit_status(t_input *input, char **token, \
			size_t *size, t_app *app);
t_token	*token_append(t_token *head, char *data, int type);
void	free_tokens(t_token *token);

#endif
