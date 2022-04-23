#include "astree.h"
#include "list.h"
#include "minishell.h"
#include "token.h"
#include <stdlib.h>

void	ft_free(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

t_list	*free_red(t_list *tks)
{
	t_list	*next;

	next = tks->next->next;
	ft_lstdelone(tks->next, free);
	ft_lstdelone(tks, free);
	return (next);
}

void	free_redirect(void *ptr)
{
	t_redirect	*red;

	red = ptr;
	free(red->file);
	free(red);
}

void	free_tree(t_node *node)
{
	if (node->type == NODE_COMMAND)
	{
		if (node->content.ast_command.cmd)
			free(node->content.ast_command.cmd);
		else
			free_mut(&node->content.ast_command.words);
	}
	else if (node->type == NODE_REDIRECTION_STATMENT)
	{
		ft_free(node->content.redirected_statement.redirections);
		free_tree(node->content.redirected_statement.body);
	}
	else if (node->type == NODE_AND || node->type == NODE_OR)
	{
		free_tree(node->content.list.left);
		free_tree(node->content.list.right);
	}
	else if (node->type == NODE_PIPE)
	{
		free_tree(node->content.leaf.right);
		free_tree(node->content.leaf.left);
	}
	free(node);
}

void	clear_tree(t_node *node, void (*del)(t_node *))
{
	if (del)
		del(node);
	else
		free(node);
}
