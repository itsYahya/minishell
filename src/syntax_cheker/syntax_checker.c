#include "minishell.h"
#include "syntax_checker.h"
#include "token.h"
#include "utils.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

t_list	*ft_checkrediriction(t_list *head, int *err, int *start)
{
	*start = 1;
	if (tk(head)->type == TK_WHITESPACE)
		head = head->next;
	if (tk(head)->type == TK_EOF)
		return (ft_return(head, err, 3));
	while (tk(head)->type != TK_EOF)
	{
		if ((tk(head)->type & (TK_LITERAL | TK_TEMPLATE_LITERAL))
			&& tk(head)->len == 1)
			return (ft_return(head, err, 2));
		else if (((tk(head)->type & (TK_LITERAL | TK_TEMPLATE_LITERAL))
				&& tk(head)->len != 1) || tk(head)->type
			& (TK_EXPRESSION | TK_ASTERISK | TK_VAR))
			return (head);
		else if (tk(head)->type == TK_WHITESPACE)
			head = head->next;
		else
			return (ft_return(head, err, 5));
	}
	return (head);
}

t_list	*ft_checkcmd_(t_list *head, int *err, int *start)
{
	if ((tk(head)->type & (TK_LITERAL | TK_TEMPLATE_LITERAL))
		&& tk(head)->len == 1)
		*err = 2;
	else if (tk(head)->type == TK_WHITESPACE)
		return (head->next);
	else if ((tk(head)->type & (TK_EXPRESSION | TK_VAR | TK_ASTERISK))
		|| ((tk(head)->type & (TK_LITERAL | TK_TEMPLATE_LITERAL))
			&& tk(head)->len != 1))
	{
		head = head->next;
		if (tk(head)->type == TK_WHITESPACE)
			head = head->next;
		*start = 1;
		if (tk(head)->type == TK_SUB_CMD)
			*err = 5;
		return (head);
	}
	else
		*err = 5;
	return (head);
}

t_list	*ft_checksub_cmd(t_list *head, int *err, int *cmd_, int *start)
{
	*cmd_ = 1;
	*start = 1;
	if (tk(head)->len == 1)
		*err = 6;
	else if (tk(head)->len == 2)
	{
		*err = 3;
		ft_errorhandler(head, *err, 1);
	}
	else
	{
		head = _checksub_cmd(head, err);
		if (!head)
			return (NULL);
	}
	if (*err && *err != 6)
		*err = 42;
	return (head->next);
}

t_list	*ft_checkcmd(t_list *head, int *err, int cmd)
{
	int		start;
	t_list	*tmp;

	start = 0;
	*err = 0;
	while (tk(head)->type != TK_EOF)
	{
		if ((tk(head)->type & (TK_PIPE | TK_OR | TK_AND)) && start)
		{
			tmp = ft_checkpao(head, err);
			if (tmp)
				return (tmp);
		}
		else if ((tk(head)->type & (TK_PIPE | TK_OR | TK_AND)) && cmd == 0)
			*err = 5;
		else if (ft_isrediriction(head))
			head = ft_checkrediriction(head->next, err, &start);
		else if (tk(head)->type == TK_SUB_CMD)
			head = ft_checksub_cmd(head, err, &cmd, &start);
		else
			head = ft_checkcmd_(head, err, &start);
		if (*err)
			return (head);
	}
	return (head);
}

int	ft_syntax_checker(t_list *tokens)
{
	t_list	*head;
	int		error;
	int		cmd;

	head = tokens;
	cmd = 0;
	while (head != 0)
	{
		head = ft_checkcmd(head, &error, cmd);
		cmd++;
		if (error)
		{
			ft_errorhandler(head, error, 0);
			return (error);
		}
		if (tk(head)->type == TK_EOF)
			break ;
	}
	return (error);
}
