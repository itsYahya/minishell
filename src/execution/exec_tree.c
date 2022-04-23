#include "astree.h"
#include "exec.h"
#include "constant.h"
#include "safe.h"
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>

int	_exec(t_context *ctx, t_simple_cmd *cmd)
{
	int		pid;
	char	*word;

	pid = -1;
	word = cmd->words.content[0];
	if (exec_builtsin(ctx, cmd, word))
		return (-1);
	word = get_cmd_path(ctx, word);
	if (word == NULL || is_dir(word, cmd->words.content[0]))
		return (free(word), close_cmd_fds(cmd));
	pid = fork();
	if (pid == -1)
		ft_perror("fork");
	if (pid == 0)
	{
		dup_cmd(cmd);
		close(cmd->out.readend);
		errno = 0;
		execve(word, (char **) cmd->words.content, (char **) ctx->env->content);
		ft_perror(word);
		if (errno == EACCES)
			exit(126);
		exit(1);
	}
	return (free(word), pid);
}

int	execute_sub_cmd(t_context *ctx, t_simple_cmd *cmd)
{
	int		pid;

	pid = -1;
	pid = fork();
	if (pid == -1)
		ft_perror("fork");
	if (pid == 0)
	{
		dup_cmd(cmd);
		close(cmd->out.readend);
		exec_shell(cmd->cmd, ctx);
		exit(ctx->last_status_code);
	}
	return (pid);
}

void	execute_cmd(t_context *ctx, t_node *cmd)
{
	int	pid;

	if (ncmd(cmd)->cmd != NULL)
		pid = execute_sub_cmd(ctx, ncmd(cmd));
	else if (ncmd(cmd)->words.len != 0)
		pid = _exec(ctx, ncmd(cmd));
	else
		ctx->last_status_code = 0;
	close_cmd_fds(ncmd(cmd));
	if (ncmd(cmd)->out.writend == -1)
		ft_wait_last(ctx, pid);
}

void	execute_redirection(t_context *ctx, t_node *red)
{
	if (read_files(red) == 0)
	{
		ctx->last_status_code = 1;
		return ;
	}
	ncmd(nred(red)->body)->in = nred(red)->pipe_in;
	ncmd(nred(red)->body)->out = nred(red)->pipe_out;
	execute_cmd(ctx, nred(red)->body);
}

void	execute(t_context *ctx, t_node *tree)
{
	if (tree == NULL)
		return ;
	if (tree->type == NODE_COMMAND)
		execute_cmd(ctx, tree);
	else if (tree->type == NODE_REDIRECTION_STATMENT)
		execute_redirection(ctx, tree);
	else if (tree->type == NODE_PIPE)
		execute_pipe(ctx, tree);
}
