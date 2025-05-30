/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkarika <fkarika@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:06:59 by fkarika           #+#    #+#             */
/*   Updated: 2025/05/26 12:32:14 by fkarika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "minishell.h"
# include "structs.h"

t_ast_node		*parse(t_token *tokens, t_app *app);
t_ast_node		*ast_new_node(t_node_types type, char **data);
t_ast_node		*ast_node_insert(t_ast_node *root,
					t_node_types type, char **data);
char			**command_data(t_token **tokens);
int				is_redir_token(int token_type);
t_node_types	redirection_type(t_token *redir);
char			**redirection_data(t_token **tokens);
void			free_ast(t_ast_node *node);

#endif
