/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkarika <fkarika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 14:54:04 by tmateja           #+#    #+#             */
/*   Updated: 2025/05/23 17:37:01 by fkarika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern volatile int	g_heredoc;

static void	sigint_handler(int sig);

/*
 * Signal handler
 * When Ctrl + C ...
 * Ignoring Ctrl + D, as it is EOF and it will be detected
 * in token.c
 */

void	sig_handler(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = sigint_handler;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

/*
 * Handler for Ctrl + C
 */

static void	sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

/**
 * @brief Signal handler for heredoc mode
 * @param sig The signal number
 */
static void	heredoc_signal_handler(int sig)
{
	if (sig == SIGINT || sig == SIGQUIT)
	{
		g_heredoc = 1;
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		write(1, "\n", 1);
		exit(130);
	}
}

/**
 * @brief Set up signal handlers for heredoc mode
 */
void	setup_heredoc_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = heredoc_signal_handler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
