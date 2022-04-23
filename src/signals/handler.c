#include "minishell.h"
#include "sig.h"
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

/*
 * signals_handler
 *
 * We use write which is a Nonreentrant function cause it uses errno
 * for that we store errno and return it back before handler return
 *
 * We also block the handler when there a child process running
 * using waitpid, this will block other signals we might lose them
 * and this what bash do;
 *
 * =====
 * Nonreentrant function :
 * https://www.gnu.org/software/libc/manual/html_node/Nonreentrancy.html
 *
 * TODO:
 * https://www.gnu.org/software/libc/manual/html_node/Termination-in-Handler.html
 * */
void	signals_handler(int sig, siginfo_t *siginfo, void *ptr)
{
	int	errtmp;

	(void) ptr;
	(void) siginfo;
	errtmp = errno;
	if (sig == SIGINT)
	{
		if (g_data.g_shell_state != SH_READING)
			return ;
		*(g_data.exit_code) = 128 + SIGINT;
		ft_putstr(2, "\n");
		RL_UNSETSTATE(RL_STATE_ISEARCH | RL_STATE_NSEARCH | RL_STATE_SEARCH
			| RL_STATE_VIMOTION | RL_STATE_NUMERICARG | RL_STATE_MULTIKEY);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	errno = errtmp;
}

/*
 * ft_init_sigaction
 *
 * this function will handle some signals so shell continue running
 * when it recieve them.
 *
 * we should mask termination signals so we can recieve one by one
 *
 * rl_catch_signals: stops readline from catching signals
 * that stops readline from printing SIGNAL CHARS to stdout
 * */
void	ft_init_sigaction(t_context *ctx)
{
	t_sigaction	sa;

	init_sig_list(ctx);
	rl_catch_signals = 0;
	memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = &signals_handler;
	sa.sa_flags = 0;
	mask_sig(&sa);
	catch_sig(&sa);
}
