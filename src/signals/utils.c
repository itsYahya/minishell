#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include "minishell.h"
#include "sig.h"

void	init_sig_list(t_context *ctx)
{
	char	**sys_siglist;

	sys_siglist = ctx->siglist;
	memset(sys_siglist, 0, NSIG * sizeof(char));
	sys_siglist[SIGHUP] = "Hangup";
	sys_siglist[SIGQUIT] = "Quit";
	sys_siglist[SIGILL] = "Illegal instruction";
	sys_siglist[SIGTRAP] = "BPT trace/trap";
	sys_siglist[SIGABRT] = "ABORT instruction";
	sys_siglist[SIGFPE] = "Floating point exception";
	sys_siglist[SIGKILL] = "Killed";
	sys_siglist[SIGBUS] = "Bus error";
	sys_siglist[SIGSEGV] = "Segmentation fault";
	sys_siglist[SIGSYS] = "Bad system call";
	sys_siglist[SIGTERM] = "Terminated";
	sys_siglist[SIGURG] = "Urgent IO condition";
	sys_siglist[SIGSTOP] = "Stopped (signal)";
	sys_siglist[SIGTSTP] = "Stopped";
	sys_siglist[SIGTTIN] = "Stopped (tty input)";
	sys_siglist[SIGTTOU] = "Stopped (tty output)";
	sys_siglist[SIGIO] = "I/O ready";
	sys_siglist[SIGXCPU] = "CPU limit";
	sys_siglist[SIGXFSZ] = "File limit";
	sys_siglist[SIGUSR1] = "User defined signal 1";
	sys_siglist[SIGUSR2] = "User defined signal 2";
}

void	mask_sig(t_sigaction *sa)
{
	sigemptyset(&sa->sa_mask);
	sigaddset(&sa->sa_mask, SIGINT);
	sigaddset(&sa->sa_mask, SIGQUIT);
}

void	catch_sig(t_sigaction *sa)
{
	sigaction(SIGINT, sa, NULL);
	sigaction(SIGQUIT, sa, NULL);
}
