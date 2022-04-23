#include "astree.h"
#include "list.h"
#include "minishell.h"
#include "token.h"
#include "parse.h"
#include "utils.h"
#include "constant.h"
#include <stdlib.h>
#include "syntax_checker.h"
#include <unistd.h>
#include <stdio.h>
#include <exec.h>

int	exec_shell(char *line, t_context *ctx)
{
	t_list	*tks;
	t_node	*tree;

	tks = tokenizer(line);
	if (tks == NULL)
		return (ctx->last_status_code = 2, -1);
	if (ft_syntax_checker(tks))
		return (ft_lstclear(&tks, free_token), ctx->last_status_code = 2, -1);
	if (!read_heredoc(ctx, tks))
		return (ft_lstclear(&tks, free_token), ctx->last_status_code = 2, -1);
	tree = parse_list(tks);
	if (tree == NULL)
		return (ft_merror("", "Failed to allocate memory"), -1);
	execute_list(ctx, tree, 1);
	clear_tree(tree, free_tree);
	return (-1);
}
