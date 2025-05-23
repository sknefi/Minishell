#ifndef SIGNALS_H
# define SIGNALS_H

extern volatile int  g_heredoc;

// TYM_COMMENT
void	sig_handler(void);
void	ignore_int_quit(void);
void	setup_heredoc_signals(void);

#endif
