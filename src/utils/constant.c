#include "constant.h"

t_token	*tk(t_list *head)
{
	return (head->content);
}

t_simple_cmd	*ncmd(t_node *node)
{
	return (&node->content.ast_command);
}

t_re_stat	*nred(t_node *node)
{
	return (&node->content.redirected_statement);
}

t_redirect	*lred(t_list *head)
{
	return (head->content);
}

t_complex_cmd	get_ccmd(t_node *node)
{
	return (node->content.complex_cmd);
}
