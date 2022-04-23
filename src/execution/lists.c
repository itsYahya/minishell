#include "astree.h"
#include "minishell.h"
#include "token.h"
#include "parse.h"
#include "utils.h"
#include "constant.h"
#include <stdlib.h>
#include "syntax_checker.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <exec.h>

t_node	*new_node(enum e_node_type type)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (node == NULL)
		return (NULL);
	memset(node, 0, sizeof(t_node));
	node->type = type;
	return (node);
}

t_node	*parse_list(t_list *tks)
{
	t_node	*complex_cmd;
	t_node	*list;
	t_list	*next;

	complex_cmd = new_node(NODE_COMPLEX_CMD);
	if (complex_cmd == NULL)
		return (NULL);
	ft_lstadd_back(&complex_cmd->content.complex_cmd.tokens, tks);
	while (!(tk(tks)->type & (TK_AND | TK_OR | TK_EOF)))
		tks = tks->next;
	next = tks->next;
	if (tk(tks)->type == TK_EOF)
		return (complex_cmd);
	list = new_node(NODE_AND);
	if (list == NULL || tks->next == NULL)
		return (free(complex_cmd), NULL);
	if (tk(tks)->type == TK_OR)
		list->type = NODE_OR;
	tk(tks)->type = TK_EOF;
	tks->next = NULL;
	list->content.list.right = complex_cmd;
	list->content.list.left = parse_list(next);
	if (list->content.list.left == NULL)
		return (free(complex_cmd), free(list), NULL);
	return (list);
}

int	execute_list(t_context *ctx, t_node *tree, int is_exec)
{
	t_node	*exec_tree;

	if (tree->type == NODE_COMPLEX_CMD)
	{
		exec_tree = parse(tree->content.complex_cmd.tokens, ctx);
		if (exec_tree == NULL)
			return (0);
		if (is_exec)
			execute(ctx, exec_tree);
		return (clear_tree(exec_tree, free_tree), 1);
	}
	else if (tree->type == NODE_OR)
	{
		execute_list(ctx, tree->content.list.right, is_exec);
		execute_list(ctx, tree->content.list.left, ctx->last_status_code != 0);
	}
	else if (tree->type == NODE_AND)
	{
		execute_list(ctx, tree->content.list.right, is_exec);
		execute_list(ctx, tree->content.list.left, ctx->last_status_code == 0);
	}
	return (1);
}
