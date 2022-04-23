#include "astree.h"
#include <stdio.h>

void	print_cmd(t_node *tree)
{
	int	i;

	i = 0;
	while (i < tree->content.ast_command.words.len)
	{
		printf("word: %s \n",
			(char *)tree->content.ast_command.words.content[i]);
		i++;
	}
}

void	print_redirection(t_node *node)
{
	t_list		*reds;
	t_redirect	*r;

	reds = node->content.redirected_statement.redirections;
	while (reds)
	{
		r = reds->content;
		printf("red : %d, %s\n", r->type, r->file);
		reds = reds->next;
	}
	print_cmd(node->content.redirected_statement.body);
}

void	print_tree(t_node *tree)
{
	if (tree->type == NODE_COMMAND)
		print_cmd(tree);
	else if (tree->type == NODE_REDIRECTION_STATMENT)
		print_redirection(tree);
}
