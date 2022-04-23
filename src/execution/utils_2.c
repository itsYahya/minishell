#include <fcntl.h>
#include "constant.h"
#include "list.h"
#include "safe.h"
#include "token.h"
#include "exec.h"
#include <stdio.h>
#include "astree.h"
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>

t_pipe	empty_pipe(void)
{
	t_pipe	p;

	p.writend = -1;
	p.readend = -1;
	return (p);
}

int	ft_pipe(t_pipe *p)
{
	int	fds[2];
	int	ret;

	ret = pipe(fds);
	if (ret < 0)
		return (ret);
	p->readend = fds[0];
	p->writend = fds[1];
	return (ret);
}

int	close_cmd_fds(t_simple_cmd *cmd)
{
	close(cmd->in.readend);
	close(cmd->out.writend);
	close(cmd->fdin);
	close(cmd->fdout);
	return (-1);
}

int	is_dir(char *filename, char *orginal)
{
	struct stat	st;

	errno = 0;
	stat(filename, &st);
	if (S_ISDIR(st.st_mode))
	{
		errno = EISDIR;
		ft_perror(orginal);
		return (1);
	}
	return (0);
}
