#include "astree.h"
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include "constant.h"
#include "list.h"
#include "safe.h"
#include "token.h"
#include "exec.h"
#include <stdio.h>

int	get_fdin(t_redirect *item, int *fdptr)
{
	int	fd;

	if (item->type == REDIRECT_IN)
		fd = open(item->file, O_RDONLY);
	else if (item->type == REDIRECT_HEREDOC)
	{	
		fd = open(item->file, O_RDONLY);
		unlink(item->file);
	}
	else
		return (1);
	if (fd == -1)
		ft_perror(item->file);
	if (*fdptr != -1)
		close(*fdptr);
	*fdptr = fd;
	return (fd != -1);
}

int	get_fdout(t_redirect *item, int *fdptr)
{
	int	fd;

	fd = 0;
	errno = 0;
	if (item->type == REDIRECT_OUT)
		fd = open(item->file, O_WRONLY
				| O_TRUNC | O_CREAT, O_CREAT_PERMISSIONS);
	else if (item->type == REDIRECT_APPEND)
		fd = open(item->file, O_WRONLY
				| O_APPEND | O_CREAT, O_CREAT_PERMISSIONS);
	else
		return (1);
	if (fd == -1)
		ft_perror(item->file);
	if (*fdptr != -1)
		close(*fdptr);
	*fdptr = fd;
	return (fd != -1);
}

int	read_files(t_node *red)
{
	t_list		*cur;
	t_node		*cmd;
	t_redirect	*item;
	int			ret;

	ret = 1;
	cmd = nred(red)->body;
	cur = nred(red)->redirections;
	while (cur)
	{
		item = cur->content;
		if (get_fdin(item, &ncmd(cmd)->fdin) == 0)
		{
			ret = 0;
			break ;
		}
		if (get_fdout(item, &ncmd(cmd)->fdout) == 0)
		{
			ret = 0;
			break ;
		}
		cur = cur->next;
	}
	ft_lstclear(&nred(red)->redirections, free_redirect);
	return (ret);
}

void	dup_cmd(t_simple_cmd *cmd)
{
	if (cmd->fdout != -1)
		dup2(cmd->fdout, STDOUT_FILENO);
	else if (cmd->out.writend != -1)
		dup2(cmd->out.writend, STDOUT_FILENO);
	if (cmd->fdin != -1)
		dup2(cmd->fdin, STDIN_FILENO);
	else if (cmd->in.readend != -1)
		dup2(cmd->in.readend, STDIN_FILENO);
	close(cmd->in.readend);
	close(cmd->fdout);
	close(cmd->fdin);
	close(cmd->out.writend);
}
