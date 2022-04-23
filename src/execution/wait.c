#include "minishell.h"
#include "utils.h"
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

void	print_signal(t_context *ctx, int status)
{
	int	sig_num;

	sig_num = WTERMSIG(status);
	if (ctx->siglist[sig_num] != 0)
		ft_putstr(2, ctx->siglist[sig_num]);
	else if (sig_num != SIGINT)
		ft_putstr(2, "Unknown Signal");
	if (WCOREDUMP(status))
		ft_putstr(2, " (core dumped)");
	ft_putstr(2, "\n");
}

pid_t	ft_waitpid(int pid, int *status, int options)
{
	pid_t	wpid;

	while (420)
	{
		errno = 0;
		wpid = waitpid(pid, status, options);
		if (errno != EINTR)
			break ;
	}
	return (wpid);
}

int	ft_wait_last(t_context *ctx, int pid)
{
	pid_t	wpid;
	int		status;
	int		tmps;

	g_data.g_shell_state = SH_WAITING;
	status = 0;
	while (69)
	{
		wpid = ft_waitpid(pid, &tmps, 0);
		if (wpid <= 0)
			break ;
		status = tmps;
	}
	if (pid != -1 && WIFSIGNALED(status))
	{
		ctx->last_status_code = 128 + WTERMSIG(status);
		print_signal(ctx, status);
	}
	else if (pid != -1)
		ctx->last_status_code = WEXITSTATUS(status);
	while (ft_waitpid(-1, &tmps, 0) >= 0)
		;
	return (1);
}
