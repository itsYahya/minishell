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

char	*_join_exp(t_list *tks, int len)
{
	t_list	*cur;
	char	*str;
	int		i;

	if (len == -1)
		count_size(tks, &len);
	cur = tks;
	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (0);
	i = 0;
	while (cur && is_word(cur))
	{
		tk_cpy(str + i, cur->content);
		i += tk_len(cur->content);
		cur = cur->next;
	}
	return (str);
}

int	join_exp(t_list *tks, int len)
{
	t_list	*cur;
	t_list	*next;
	char	*str;

	str = _join_exp(tks, len);
	if (str == NULL)
		return (0);
	cur = tks->next;
	while (cur && tk(cur)->type & (TK_EXPRESSION | TK_ASTERISK))
	{
		next = cur->next;
		ft_lstdelone(cur, free_token);
		cur = next;
	}
	if (tk(tks)->len == -1)
		free(tk(tks)->value);
	return (tk_set(tks->content, TK_EXPRESSION, str, -1));
}

int	_join(t_list **head, t_list **cur, char *str, int check_ambg)
{
	int		len;
	t_list	*next;
	t_list	*tmp;

	next = count_size(*cur, &len);
	if (has_tk(*cur, TK_ASTERISK))
	{
		tmp = match(*cur);
		check_ambg = (check_ambg && ft_lstsize(tmp) != 1);
		if (tmp && !check_ambg)
		{
			ft_lstadd_back(head, tmp);
			return (ft_lstclear(cur, free_token),*cur = next, 1);
		}
		if (check_ambg && tmp != NULL)
		{
			ft_merror(str, " : ambiguous redirect\n");
			ft_lstclear(cur, free_token);
			return (ft_lstclear(&tmp, free_token), 0);
		}
	}
	join_exp(*cur, len);
	(*cur)->next = NULL;
	ft_lstadd_back(head, *cur);
	return (*cur = next, 1);
}

/*
 * cur = tokens after expansion
 * */
int	join_words(t_context *ctx, t_list **head, int is_red_fellow)
{
	t_list	*item;
	char	*str;

	item = *head;
	str = _join_exp(item, -1);
	if (str == NULL)
		return (0);
	if (!expand(ctx, &item))
		return (free(str), ft_lstclear(&item, free_token), 0);
	if ((item == NULL || has_tk(item, TK_WHITESPACE)) && is_red_fellow)
	{
		ft_merror(str, " : ambiguous redirect\n");
		return (free(str), ft_lstclear(&item, free_token), 0);
	}
	*head = NULL;
	while (item)
	{
		item = tk_ignore(item, TK_WHITESPACE, 1);
		if (item && !_join(head, &item, str, is_red_fellow))
			return (free(str), ft_lstclear(head, free_token), 0);
		is_red_fellow = 0;
	}
	return (free(str), 1);
}

t_list	*join(t_context *ctx, t_list *tks)
{
	t_list				*head;
	t_list				*next;
	enum e_token_type	type;

	head = NULL;
	type = TK_EOF;
	while (tks)
	{
		next = tks->next;
		if (is_word(tks))
		{
			next = tk_ignore(next, TK_WORDABLE, 0);
			if (!join_words(ctx, &tks, is_redirection(type)))
				return (ft_lstclear(&next, free_token),
					ft_lstclear(&head, free_token), NULL);
		}
		else
			tks->next = NULL;
		if (tks)
			type = tk(tks)->type;
		ft_lstadd_back(&head, tks);
		tks = next;
	}
	return (head);
}
