#include "list.h"
#include "token.h"
#include "utils.h"
#include "constant.h"
#include "minishell.h"
#include "parse.h"
#include <stdlib.h>

int	expand(t_context *ctx, t_list **head)
{
	t_list	*cur;
	t_list	*next;

	cur = *head;
	*head = NULL;
	while (cur && is_word(cur))
	{
		next = cur->next;
		cur->next = NULL;
		if (tk(cur)->type == TK_VAR)
			expand_var(ctx, head, cur);
		else
		{
			if (!expand_oth(ctx, head, cur))
				return (0);
		}
		cur = next;
	}
	return (1);
}

int	has_tk(t_list *tks, enum e_token_type type)
{
	while (tks)
	{
		if (tk(tks)->type == type)
			return (1);
		tks = tks->next;
	}
	return (0);
}

int	is_word(t_list *item)
{
	return (tk(item)->type & (TK_WORDABLE));
}

int	is_redirection(enum e_token_type type)
{
	return (type & (TK_REDIRICT_IN | TK_REDIRICT_OUT | TK_APPEND | TK_HEREDOC));
}

void	del_spaces(t_list **head)
{
	t_list	*last;
	t_list	*next;
	t_list	*cur;

	last = NULL;
	next = NULL;
	cur = *head;
	while (cur)
	{
		next = cur->next;
		if (tk(cur)->type == TK_WHITESPACE)
		{
			ft_lstdelone(cur, free_token);
			if (last == NULL)
			{
				*head = next;
				cur = NULL;
			}
			else
				last->next = next;
		}
		if (last == NULL || last->next != next)
			last = cur;
		cur = next;
	}
}
