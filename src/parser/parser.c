#include <stdlib.h>
#include "astree.h"
#include "list.h"
#include "minishell.h"
#include "token.h"
#include "utils.h"
#include "parse.h"
#include "exec.h"
#include "constant.h"

int	add_redirect(t_node **tree_ptr, t_node *body, t_list **tks)
{
	t_list	*node;

	if ((*tree_ptr)->type == NODE_COMMAND)
	{
		*tree_ptr = new_red_node(body);
		if (*tree_ptr == NULL)
			return (free_tree(body), 0);
	}
	node = new_red(tk((*tks)->next)->value);
	if (node == NULL)
		return (free_tree(*tree_ptr), 0);
	if (tk(*tks)->type == TK_HEREDOC)
		lred(node)->type = REDIRECT_HEREDOC;
	else if (tk(*tks)->type == TK_REDIRICT_OUT)
		lred(node)->type = REDIRECT_OUT;
	else if (tk(*tks)->type == TK_REDIRICT_IN)
		lred(node)->type = REDIRECT_IN;
	else if (tk(*tks)->type == TK_APPEND)
		lred(node)->type = REDIRECT_APPEND;
	ft_lstadd_back(&nred(*tree_ptr)->redirections, node);
	*tks = free_red(*tks);
	return (1);
}

t_node	*new_cmd_node(t_list *tks)
{
	t_node	*node;

	node = new_node(NODE_COMMAND);
	if (node == NULL)
		return (NULL);
	ncmd(node)->cmd = NULL;
	if (tk(tks)->type == TK_SUB_CMD)
		ncmd(node)->cmd = ft_dup_norm(tks);
	node->type = NODE_COMMAND;
	ncmd(node)->fdin = -1;
	ncmd(node)->fdout = -1;
	ncmd(node)->in = empty_pipe();
	ncmd(node)->out = empty_pipe();
	init_mut(&ncmd(node)->words, 100);
	return (node);
}

t_node	*parse_cmd(t_context *ctx, t_list *tks)
{
	t_node	*root;
	t_node	*node;
	t_list	*next;

	node = new_cmd_node(tks);
	root = node;
	while (node && tks)
	{
		next = tks->next;
		if (tk(tks)->type == TK_EOF)
			return (ft_lstdelone(tks, free), root);
		else if (tk(tks)->type == TK_PIPE)
			return (parse_pipe(ctx, root, tks));
		else if (is_redirection(tk(tks)->type))
			if (add_redirect(&root, node, &tks))
				continue ;
		else
			return (ft_lstclear(&tks, free_token), NULL);
		else if (tk(tks)->type == TK_EXPRESSION)
			if (!mut_add(&ncmd(node)->words, tk(tks)->value))
				return (ft_lstclear(&tks, free_token), free_tree(node), NULL);
		ft_lstdelone(tks, free);
		tks = next;
	}
	return (root);
}

/*
 * parse_pipe
 *
 * @param root : a pointer to tree root
 *
 * @param tokens : a linked list(t_list)
 * points to TK_PIPE token
 *
 * takes the root and make it a child of the pipe node 
 * which the new root
 *
 * starts parsing recursively again from next token 
 * and attach the returned root to right side of the root
 *
 * chad a f
 * */
t_node	*parse_pipe(t_context *ctx, t_node *root, t_list *tokens)
{
	t_node	*new_root;

	new_root = malloc(sizeof(t_node));
	if (new_root == NULL)
		return (ft_lstclear(&tokens, free_token), free(root), NULL);
	new_root->type = NODE_PIPE;
	new_root->content.leaf.pipe_in = empty_pipe();
	new_root->content.leaf.right = root;
	new_root->content.leaf.left = parse_cmd(ctx, tokens->next);
	if (new_root->content.leaf.left == NULL)
	{
		free(root);
		free(new_root);
		ft_lstclear(&tokens, free_token);
		return (NULL);
	}
	ft_lstdelone(tokens, free_token);
	return (new_root);
}

/**
 * expand vars drops TK_VAR TK_TEMPLATE TK_LITTERAL
 * join TK_EXPRESSION
 * delete WHITESPACES
 * return tree
 **/
t_node	*parse(t_list *tokens, t_context *ctx)
{
	tokens = join(ctx, tokens);
	del_spaces(&tokens);
	if (tokens == NULL || tk(tokens)->type == TK_EOF)
		return (NULL);
	return (parse_cmd(ctx, tokens));
}
