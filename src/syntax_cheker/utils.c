#include "minishell.h"
#include "syntax_checker.h"
#include "utils.h"
#include <stdio.h>
#include <unistd.h>

void	ft_errorhandler(t_list *head, int err, int pr)
{
	(void)head;
	if (err == 2)
		ft_merror("syntax error near ", "unclosed quote\n");
	else if (err == 3)
	{
		if (pr == 0)
			ft_merror("syntax error near ", "unexpected token `newline'\n");
		else
			ft_merror("syntax error near ", "unexpected token `)'\n");
	}
	else if (err == 4)
		ft_merror("syntax error near ", "unclosed pipe\n");
	else if (err == 6)
		ft_merror("syntax error near ", "unclosed parenthesis\n");
	else if (err == 5)
	{
		ft_merror("syntax error near ", "unexpected token `");
		if (tk(head)->type == TK_SUB_CMD)
			write(2, "(", 1);
		else
			write(2, tk(head)->value, tk(head)->len);
		ft_putstr(2, "'\n");
	}
}

t_list	*ft_return(t_list *head, int *err, int error)
{
	*err = error;
	return (head);
}

t_list	*ft_checkpao(t_list *head, int *err)
{
	head = head->next;
	if (tk(head)->type == TK_WHITESPACE)
		head = head->next;
	if (tk(head)->type != TK_EOF)
		return (head);
	*err = 4;
	return (0);
}

int	ft_isrediriction(t_list *head)
{
	return (tk(head)->type == TK_APPEND || tk(head)->type == TK_HEREDOC
		|| tk(head)->type == TK_REDIRICT_IN
		|| tk(head)->type == TK_REDIRICT_OUT);
}
