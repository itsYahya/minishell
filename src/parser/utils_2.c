#include "list.h"
#include "minishell.h"
#include "token.h"
#include "utils.h"
#include "parse.h"
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include "constant.h"
#include "exec.h"

t_list	*new_red(char *file)
{
	t_list		*node;
	t_redirect	*red;

	red = malloc(sizeof(t_redirect));
	node = ft_lstnew(red);
	if (node == NULL || red == NULL)
	{
		free(node);
		free(red);
		return (NULL);
	}
	red->file = file;
	return (node);
}

t_node	*new_red_node(t_node *body)
{
	t_node	*node;

	node = new_node(NODE_REDIRECTION_STATMENT);
	if (node == NULL)
		return (NULL);
	nred(node)->body = body;
	nred(node)->redirections = 0;
	nred(node)->pipe_in = empty_pipe();
	nred(node)->pipe_out = empty_pipe();
	return (node);
}
