#include "astree.h"
#include "minishell.h"
#include "exec.h"
#include "constant.h"
#include <unistd.h>
#include <stdlib.h>

void	exec_right(t_context *ctx, t_node *tree, t_pipe pipe)
{
	t_node	*node;

	node = tree->content.leaf.right;
	if (node->type == NODE_COMMAND)
	{
		ncmd(node)->out = pipe;
		ncmd(node)->in = tree->content.leaf.pipe_in;
		execute_cmd(ctx, node);
	}
	else if (node->type == NODE_REDIRECTION_STATMENT)
	{
		(nred(node))->pipe_in = tree->content.leaf.pipe_in;
		(nred(node))->pipe_out = pipe;
		execute_redirection(ctx, node);
	}
	else
	{
		ft_putstr(2, "Programming error: Unexpected right PIPE node");
		exit(2);
	}
}

void	exec_left(t_context *ctx, t_node *tree, t_pipe pipe)
{
	t_node	*node;

	node = tree->content.leaf.left;
	if (node->type == NODE_PIPE)
	{
		node->content.leaf.pipe_in = pipe;
		node->content.leaf.pipe_out = empty_pipe();
		execute_pipe(ctx, node);
	}
	else if (node->type == NODE_REDIRECTION_STATMENT)
	{
		(nred(node))->pipe_in = pipe;
		(nred(node))->pipe_out = empty_pipe();
		execute_redirection(ctx, node);
	}
	else
	{
		ncmd(node)->in = pipe;
		ncmd(node)->out = empty_pipe();
		execute_cmd(ctx, node);
	}
}

void	execute_pipe(t_context *ctx, t_node *tree)
{
	t_pipe	pipe;

	if (ft_pipe(&pipe) < 0)
		return ;
	exec_right(ctx, tree, pipe);
	exec_left(ctx, tree, pipe);
	close(pipe.writend);
	close(pipe.readend);
}
