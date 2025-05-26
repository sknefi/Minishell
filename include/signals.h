/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkarika <fkarika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:08:04 by fkarika           #+#    #+#             */
/*   Updated: 2025/05/26 17:29:14 by fkarika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

static volatile int	g_heredoc;

// TYM_COMMENT
void	sig_handler(void);
void	ignore_int_quit(void);
void	default_int_quit(void);
void	setup_heredoc_signals(void);

#endif
